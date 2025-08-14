# co_stream
## Introduction
co_stream is a high-performance asynchronous network programming library developed based on C++20 coroutines and libuv. Leveraging C++20 coroutine features, it transforms traditional asynchronous programming patterns into a synchronous-style coding approach, significantly reducing the complexity of asynchronous network development while maintaining high performance.


## Core Features
* Native C++20 coroutine support: Utilizes C++20 standard coroutines (syntax like `co_await`, `co_return`), making the writing of asynchronous operations as intuitive as synchronous code and completely eliminating the hassle of callback nesting (Callback Hell).
* Built on libuv engine: Relies on the mature libuv cross-platform asynchronous I/O library as the underlying support, inheriting its core capabilities such as efficient event loops, network operations, and timers to ensure stable and reliable underlying performance.
* High-performance network communication: Optimized for high-concurrency scenarios, supporting efficient management of massive TCP connections, and maintaining low latency and high throughput even under high loads.
* Rich network components:
  - Comprehensive TCP protocol support, including implementations of high-performance TCP servers and clients.
  - Built-in lightweight and high-performance HTTP server, supporting route management and asynchronous request processing.
* Cross-platform compatibility: Seamlessly supports mainstream operating systems such as Windows, Linux, and macOS. The unified API interface ensures a consistent development experience across multiple platforms.


## Application Scenarios
* High-concurrency TCP services (e.g., instant messaging servers, game servers, IoT data acquisition gateways, etc.)
* High-performance HTTP services (e.g., API gateways, lightweight web services, data interface services, etc.)
* Network application development that requires asynchronous I/O but aims to simplify the programming model


## Dependencies
* Compiler: C++20-compliant compilers (GCC 11+, Clang 13+, MSVC 2022+)
* Third-party library: libuv 1.44.2 or higher
* Build tool: CMake 3.18 or higher


## License
co_stream is open-sourced under the MIT License, which permits free use, modification, and distribution. For details, refer to the LICENSE file.