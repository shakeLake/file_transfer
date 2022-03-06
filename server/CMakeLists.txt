cmake_minimum_required(VERSION 3.2)

project(server)

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.78 REQUIRED COMPONENTS system thread)

add_library(serverLib server.cpp server.hpp session.cpp session.hpp)
add_executable(startServer main.cpp)

target_link_libraries(startServer serverLib Boost::system Boost::thread)
