cmake_minimum_required(VERSION 3.14)
project(ServidorFTP)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")

find_package(Threads)

add_executable(ServidorFTP src/ClientConnection.h src/common.h src/FTPServer.h
                src/ClientConnection.cpp src/FTPServer.cpp src/ftp_server.cpp)

target_link_libraries(ServidorFTP ${CMAKE_THREAD_LIBS_INIT})