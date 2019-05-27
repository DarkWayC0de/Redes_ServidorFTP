cmake_minimum_required(VERSION 3.14)
project(ServidorFTP)

set(CMAKE_CXX_STANDARD 14)

add_executable(ServidorFTP src/ClientConnection.cpp src/ClientConnection.h src/common.h src/ftp_server.cpp
        src/FTPServer.cpp src/FTPServer.h)