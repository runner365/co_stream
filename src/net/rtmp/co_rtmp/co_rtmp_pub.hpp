#ifndef CO_RTMP_PUB_HPP
#define CO_RTMP_PUB_HPP
#include "utils/logger.hpp"
#include <stdint.h>
#include <stddef.h>
#include <string>

namespace cpp_streamer
{
#define RTMP_OK               0
#define RTMP_NEED_READ_MORE   1
#define RTMP_SIMPLE_HANDSHAKE 2
#define CHUNK_DEF_SIZE        128

typedef enum {
    initial_phase = -1,
    handshake_c2_phase,
    connect_phase,
    create_stream_phase,
    create_publish_play_phase,
    media_handle_phase
} RTMP_SERVER_SESSION_PHASE;

}

#endif