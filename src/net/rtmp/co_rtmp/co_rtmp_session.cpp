#include "co_rtmp_session.hpp"
#include "net/tcp/co_tcp/co_tcp_server/co_tcp_accept_conn.hpp"

namespace cpp_streamer
{

CoRtmpSession::CoRtmpSession(std::shared_ptr<TcpCoAcceptConn> conn_ptr, Logger* logger)
    : logger_(logger)
    , recv_buffer_(64 * 1024)
    , hs_(logger)
{
    conn_ptr_ = conn_ptr;
    memset(recv_data_, 0, sizeof(recv_data_));
}

CoRtmpSession::~CoRtmpSession()
{
}

bool CoRtmpSession::IsAlive() const {
    return true;
}

CoVoidTask CoRtmpSession::Run() {
    while (true) {
        if (closed_) {
            LogInfof(logger_, "RTMP session is closed, exiting Run loop.");
            co_return;
        }
        RecvResult result = co_await conn_ptr_->CoReceive(recv_data_, sizeof(recv_data_));
        if (result.status != RECV_OK) {
            LogErrorf(logger_, "Failed to receive data, status: %d, length: %d", result.status, result.recv_len);
            break;
        }

        recv_buffer_.AppendData((char*)recv_data_, sizeof(recv_data_));

        HandleRequest();
    }
    closed_ = false;
}

CoTask<int> CoRtmpSession::HandleRequest() {
    int ret = RTMP_OK;

    if (phase_ == initial_phase) {
        LogInfof(logger_, "RTMP session is in initial phase, handling C0C1 handshake.");
        ret = hs_.HandleC0C1(recv_buffer_);
        if (ret < 0) {
            LogErrorf(logger_, "handle C0C1 error, ret: %d", ret);
            closed_ = true;
            co_return ret;
        }
        if (ret == RTMP_NEED_READ_MORE) {
            LogInfof(logger_, "need read more data for C0C1");
            co_return ret;
        }
        if (ret == RTMP_SIMPLE_HANDSHAKE) {
            LogInfof(logger_, "try to rtmp handshake in simple mode");
        }
        recv_buffer_.Reset();

        std::vector<uint8_t> s0s1s2;
        ret = hs_.SendS0S1S2(s0s1s2);
        if (ret < 0) {
            LogErrorf(logger_, "Failed to send S0S1S2, ret: %d", ret);
            closed_ = true;
            co_return ret;
        }
        SendResult result = co_await conn_ptr_->CoSend(s0s1s2.data(), s0s1s2.size());
        if (result.status != SEND_OK) {
            LogErrorf(logger_, "Failed to send S0S1S2, status: %d", result.status);
            co_return -1;
        }
        phase_ = handshake_c2_phase;
    } else if (phase_ == handshake_c2_phase) {
        LogInfof(logger_, "RTMP session is in handshake C2 phase, handling C2 handshake.");
        ret = hs_.HandleC2(recv_buffer_);
        if (ret < 0) {
            LogErrorf(logger_, "handle C2 error, ret: %d", ret);
            closed_ = true;
            co_return ret;
        }
        if (ret == RTMP_NEED_READ_MORE) {
            LogInfof(logger_, "need read more data for C2");
            co_return ret;
        }
        phase_ = connect_phase;
        LogInfof(logger_, "RTMP session phase changed to connect_phase, recv buffer len:%zu",
                recv_buffer_.DataLen());
        if (recv_buffer_.DataLen() == 0) {
            LogInfof(logger_, "RTMP session has no data in buffer");
            co_return RTMP_NEED_READ_MORE;
        }
    }
    co_return ret;
}
}