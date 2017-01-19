#cmake_minimum_required(VERSION 3.6)
#project(ClientAss3)
#
#set(CMAKE_CXX_STANDARD 11)
#
#set(SOURCE_FILES main.cpp src/BidiEncoderDecoder.cpp include/BidiEncoderDecoder.h src/Client.cpp src/ConnectionHandler.cpp include/ConnectionHandler.h src/KeyBoardListener.cpp include/KeyBoardListener.h src/ServerListener.cpp include/ServerListener.h src/Packets/DATAPacket.cpp include/Packets/DATAPacket.h src/Packets/ACKPacket.cpp include/Packets/ACKPacket.h src/Packets/BasePacket.cpp include/Packets/BasePacket.h src/Packets/BCASTPacket.cpp include/Packets/BCASTPacket.h src/Packets/DELRQPacket.cpp include/Packets/DELRQPacket.h src/Packets/DIRQPacket.cpp include/Packets/DIRQPacket.h src/Packets/DISCPacket.cpp include/Packets/DISCPacket.h src/Packets/ERRORPacket.cpp include/Packets/ERRORPacket.h src/Packets/LOGRQPacket.cpp include/Packets/LOGRQPacket.h src/Packets/RRQWRQPacket.cpp include/Packets/RRQWRQPacket.h)
#add_executable(ClientAss3 ${SOURCE_FILES})





cmake_minimum_required(VERSION 3.6)

project(ClientAss3)


find_package(Boost 1.57.0 COMPONENTS system filesystem thread REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/BidiEncoderDecoder.cpp include/BidiEncoderDecoder.h src/Client.cpp src/ConnectionHandler.cpp include/ConnectionHandler.h src/KeyBoardListener.cpp include/KeyBoardListener.h src/ServerListener.cpp include/ServerListener.h src/Packets/DATAPacket.cpp include/Packets/DATAPacket.h src/Packets/ACKPacket.cpp include/Packets/ACKPacket.h src/Packets/BasePacket.cpp include/Packets/BasePacket.h src/Packets/BCASTPacket.cpp include/Packets/BCASTPacket.h src/Packets/DELRQPacket.cpp include/Packets/DELRQPacket.h src/Packets/DIRQPacket.cpp include/Packets/DIRQPacket.h src/Packets/DISCPacket.cpp include/Packets/DISCPacket.h src/Packets/ERRORPacket.cpp include/Packets/ERRORPacket.h src/Packets/LOGRQPacket.cpp include/Packets/LOGRQPacket.h)
add_executable(ClientAss3 ${SOURCE_FILES})

if(Boost_FOUND)

    target_link_libraries(ClientAss3 ${Boost_LIBRARIES})

endif()


