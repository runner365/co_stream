#include "co_rtmp_server.hpp"
#include "utils/logger.hpp"

using namespace cpp_streamer;
Logger* logger = nullptr;

int main(int argc, char* argv[]) {
    // Initialize logger
    Logger* logger = new Logger("rtmp_server.log");
    logger->EnableConsole();

    // Create an event loop
    uv_loop_t* loop = uv_default_loop();

    // Create and run the RTMP server
    LogInfof(logger, "Starting RTMP server...");
    cpp_streamer::RtmpServer rtmp_server(loop, "0.0.0.0", 1935, logger);

    rtmp_server.Run();

    // Run the event loop
    LogInfof(logger, "Starting RTMP server on 0.0.0.0:1935");
    uv_run(loop, UV_RUN_DEFAULT);

    delete logger;
    return 0;
}