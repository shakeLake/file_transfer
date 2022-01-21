cmake_minimum_required(VERSION 3.2)

project(client)

find_package(Boost 1.78 REQUIRED COMPONENTS system thread)

add_library(client client.cpp client.hpp)
add_executable(start main.cpp)

target_link_libraries(start client Boost::system Boost::thread)
