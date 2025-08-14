#ifndef RTMP_SERVER_HPP
#define RTMP_SERVER_HPP
#include "utils/co_pub.hpp"
#include "utils/timer.hpp"
#include "utils/logger.hpp"
#include "net/tcp/co_tcp/co_tcp_server/co_tcp_server.hpp"
#include <memory>
#include <map>
#include <string>

namespace cpp_streamer
{

class CoRtmpSession;
class RtmpServer : public TimerInterface
{
public:
    RtmpServer(uv_loop_t* loop,
            const std::string& host,
            int port,
            Logger* logger);
    virtual ~RtmpServer();

    CoVoidTask Run();

protected:
    void OnTimer() override;

private:
    void OnCheckAlive(int64_t now_ms);

private:
    std::unique_ptr<CoTcpServer> tcp_server_;
    Logger* logger_ = nullptr;

private:
    std::map<std::string, std::shared_ptr<CoRtmpSession>> sessions_;
    int64_t last_check_ms_ = -1;
};
}

#endif