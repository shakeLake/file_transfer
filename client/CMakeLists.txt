cmake_minimum_required(VERSION 3.22)

project(client)

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.78 REQUIRED COMPONENTS system thread)

add_library(client client.cpp client.hpp)
add_executable(startClient main.cpp)

target_link_libraries(startClient client Boost::system Boost::thread)
