#ifndef CO_RTMP_SESSION_HPP
#define CO_RTMP_SESSION_HPP
#include "utils/logger.hpp"
#include "utils/data_buffer.hpp"
#include "utils/co_pub.hpp"
#include "net/tcp/co_tcp/co_tcp_server/co_tcp_accept_conn.hpp"
#include "co_rtmp_pub.hpp"
#include "co_rtmp_handshake.hpp"
#include <memory>
#include <string>

namespace cpp_streamer
{

class CoRtmpSession
{
public:
    CoRtmpSession(std::shared_ptr<TcpCoAcceptConn> conn_ptr, Logger* logger);
    ~CoRtmpSession();

public:
    CoVoidTask Run();

public:
    bool IsAlive() const;

public:
    CoTask<int> HandleRequest();

private:
    std::shared_ptr<TcpCoAcceptConn> conn_ptr_;
    Logger* logger_ = nullptr;

private:
    uint8_t recv_data_[10 * 1024] = {0}; // 20K read buffer
    DataBuffer recv_buffer_;

private:
    RTMP_SERVER_SESSION_PHASE phase_ = initial_phase;
    bool closed_ = false;

private:
    RtmpServerHandshake hs_;
};

}
#endif // CO_RTMP_SESSION_HPP