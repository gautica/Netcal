cmake_minimum_required(VERSION 2.8)

project (Netcal)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

add_subdirectory(server)

add_subdirectory(client)
