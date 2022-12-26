cmake_minimum_required(VERSION 3.2)

project(client)

find_package(Boost REQUIRED COMPONENTS system thread)

add_library(client client.cpp client.hpp)
add_executable(startClient main.cpp)

target_link_libraries(startClient client Boost::system Boost::thread)
