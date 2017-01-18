cmake_minimum_required(VERSION 3.6)
project(ClientAss3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/BidiEncoderDecoder.cpp include/BidiEncoderDecoder.h src/Client.cpp src/ConnectionHandler.cpp include/ConnectionHandler.h src/KeyBoardListener.cpp include/KeyBoardListener.h src/ServerListener.cpp include/ServerListener.h)
add_executable(ClientAss3 ${SOURCE_FILES})