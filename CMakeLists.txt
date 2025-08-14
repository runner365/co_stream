cmake_minimum_required(VERSION 3.7.1)
project(cpp_streamer)

#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wno-deprecated -Wno-deprecated-declarations -Wno-reorder -Wall -fexceptions -frtti -D__STDC_FORMAT_MACROS -fPIC")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++20 -g -Wno-deprecated -Wno-deprecated-declarations -Wall -fexceptions -frtti -D__STDC_FORMAT_MACROS -fPIC")


set(CMAKE_OUTPUT_BASE ${CMAKE_BINARY_DIR}/output)
set(BUILD_OUTPUT_BASE ${CMAKE_BINARY_DIR}/output)
set(PREFIX_DIR "${BUILD_OUTPUT_BASE}")
set(INSTALL_RPATH "${PREFIX_DIR}/lib")

# set output static libary
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output/lib)

# set pkgconfig path
set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/output/lib/pkgconfig")

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
if (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
message("-----This is MacOs arm64")
else()
message("-----This is MacOs Intel")
endif()
else()
message("-----This is system ${CMAKE_SYSTEM_NAME}")
endif()
message("-----------------------------------------------")
message("-----------------------------------------------")
message("-----------------------------------------------")

# set include path
include_directories(${CMAKE_BINARY_DIR}/output/include
                    ${CMAKE_BINARY_DIR}/output/include/openssl
                    src
                    src/net
                    src/net/tcp
                    src/net/tcp/co_tcp
                    src/net/tcp/co_tcp/co_tcp_client
                    src/net/tcp/co_tcp/co_tcp_server
                    src/utils
                    src/utils/av
                    /usr/local/include)

# set lib path
IF (APPLE)
link_directories(${CMAKE_BINARY_DIR}/output/lib /usr/local/lib)
ELSEIF (UNIX)
link_directories(${CMAKE_BINARY_DIR}/output/lib /usr/local/lib64 /usr/local/lib)
ENDIF ()

add_subdirectory(3rdparty)

################################################################
# example: tcp co client demo
add_executable(co_tcp_client_demo
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_client/co_tcp_conn.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_client/co_tcp_conn_send.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_client/co_tcp_conn_recv.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_pub.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_client/co_tcp_client_echo.cpp)
add_dependencies(co_tcp_client_demo uv)
IF (APPLE)
target_link_libraries(co_tcp_client_demo dl z m uv)
ELSEIF (UNIX)
target_link_libraries(co_tcp_client_demo rt dl z m pthread uv)
ENDIF ()

################################################################
# example: tcp co server demo
add_executable(co_tcp_server_demo
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_server.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_session_send.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_session_recv.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_accept_conn.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_pub.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_server_echo.cpp)
add_dependencies(co_tcp_server_demo uv)
IF (APPLE)
target_link_libraries(co_tcp_server_demo dl z m uv)
ELSEIF (UNIX)
target_link_libraries(co_tcp_server_demo rt dl z m pthread uv)
ENDIF ()

################################################################
# example: http co server demo
add_executable(co_http_server_demo
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_server.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_session_send.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_session_recv.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_accept_conn.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_pub.cpp
            ${PROJECT_SOURCE_DIR}/src/net/http/co_http/co_http_server.cpp
            ${PROJECT_SOURCE_DIR}/src/net/http/co_http/co_http_common.cpp
            ${PROJECT_SOURCE_DIR}/src/net/http/co_http/co_http_session.cpp
            ${PROJECT_SOURCE_DIR}/src/net/http/co_http/co_http_server_demo.cpp)
add_dependencies(co_http_server_demo uv)
IF (APPLE)
target_link_libraries(co_http_server_demo dl z m uv)
ELSEIF (UNIX)
target_link_libraries(co_http_server_demo rt dl z m pthread uv)
ENDIF ()

################################################################
# example: co rtmp server
add_executable(co_rtmp_server
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_server.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_session_send.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_session_recv.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_server/co_tcp_accept_conn.cpp
            ${PROJECT_SOURCE_DIR}/src/net/tcp/co_tcp/co_tcp_pub.cpp
            ${PROJECT_SOURCE_DIR}/src/net/rtmp/co_rtmp/co_rtmp_server.cpp
            ${PROJECT_SOURCE_DIR}/src/net/rtmp/co_rtmp/co_rtmp_session.cpp
            ${PROJECT_SOURCE_DIR}/src/net/rtmp/co_rtmp/co_rtmp_handshake.cpp
            ${PROJECT_SOURCE_DIR}/src/net/rtmp/co_rtmp/co_rtmp_server_instance.cpp
            )
add_dependencies(co_rtmp_server openssl uv)
IF (APPLE)
target_link_libraries(co_rtmp_server dl z m ssl crypto uv)
ELSEIF (UNIX)
target_link_libraries(co_rtmp_server rt dl z m pthread ssl crypto uv)
ENDIF ()