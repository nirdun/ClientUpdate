//
// Created by ניר דוניץ on 15.1.2017.
//


#include <boost/thread/pthread/thread_data.hpp>
#include "../include/ServerListener.h"
#include "../include/BidiEncoderDecoder.h"
#include "packets/BasePacket.h"
#include "packets/BCASTPacket.h"
#include "packets/ERRORPacket.h"
#include "packets/ACKPacket.h"
#include "packets/DATAPacket.h"
#include <fstream>
#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;

#include <iostream>
#include <boost/thread/thread.hpp>

ServerListener::ServerListener(ConnectionHandler &handler) :
        _handler(handler),
        _listenerType("server") {}

void ServerListener::run() {
    BidiEncoderDecoder *encoderDecoder;
    while (!_handler.shouldTerminate()) {
        BasePacket *packetFromServer;

        packetFromServer = _handler.processServerPakect();
        createResponse(packetFromServer);

    }

}

void ServerListener::createResponse(BasePacket *packetFromServer) {
    int currentAct = _handler.getCurrentAction();
    switch (packetFromServer->getOpCode()) {
        //DATA
        case 3: {
            char *data = (static_cast<DATAPacket *>(packetFromServer))->getData();
            dataFromServer.insert(dataFromServer.end(), data, data + strlen(data));
            short dataSize = (static_cast<DATAPacket *>(packetFromServer))->getPacketSize();
            short blockNumber = (static_cast<DATAPacket *>(packetFromServer))->getBlockNum();
            //downloading
            if (currentAct == 1) {
                if (dataSize != 512) {
                    std::ofstream stream;
                    if (boost::filesystem::exists(_handler.getFileName())) {
                        stream.open("./" + _handler.getFileName(), std::ofstream::binary | std::ofstream::app);
                    } else {//file exist
                        stream.open("./" + _handler.getFileName(),
                                    std::ofstream::binary | std::ofstream::app | std::ofstream::trunc);

                    }

                    if (stream.is_open()) {
                        for (unsigned int i = 0; i < dataFromServer.size(); i++) {
                            stream.put(dataFromServer.at(i));
                        }
                        stream.close();
                    }
                    delete (data);
                    dataFromServer.clear();

                }
                std::string blockString = to_string(blockNumber);
                _handler.encodeAndSend("ACK " + blockString);
            }
                //dir
            else if (currentAct == 6) {
                if (dataSize != 512) {
                    std::string printDir(dataFromServer.begin(), dataFromServer.end());
                    std::cout << printDir << std::endl;
                    dataFromServer.clear();
                }
            }
            break;
        }

            //ACK
        case 4: {
            switch (currentAct) {
                //WRQ
                case 2: {
                    (static_cast<ACKPacket *>(packetFromServer))->printACK();
                    short blockNum = (static_cast<ACKPacket *>(packetFromServer))->getBlockNum();
                    if (blockNum == 0) {
                        //open "filename" read from it to map of vectors of chars and send first packet
                        std::ifstream stream;
                        stream.open(_handler.getFileName(), std::ifstream::binary);
                        long fileSize = stream.tellg();
                        int countBlock = 1;
                        int i = 0;
                        while (i < fileSize) {
                            for (int j = 0; j < 512 && i < fileSize; j++) {
                                //todo check ++i
                                dataMapToSend[countBlock].push_back(stream.get());
                                stream.seekg(i);
                                i++;
                            }
                            countBlock++;
                        }
                        stream.close();

                    }
                    if (blockNum < dataMapToSend.size())
                    {
                        DATAPacket *dataPacketToSend = new DATAPacket((short) dataMapToSend[blockNum + 1].size(),
                                                                      blockNum + 1,

                                                                      dataMapToSend[blockNum + 1].data());
                        int sizeOfPacket = dataMapToSend[blockNum + 1].size() + 6;
                        char *bytesToSend = new char[sizeOfPacket];
                        shortToBytes(4, bytesToSend);
                        char blockNumArr[2];
                        shortToBytes(blockNum + 1, blockNumArr);
                        char packetSizeArr[2];
                        shortToBytes((short) sizeOfPacket, packetSizeArr);
                        _handler.mergeArrays(bytesToSend, packetSizeArr, 2);
                        _handler.mergeArrays(bytesToSend, blockNumArr, 4);

                        _handler.sendBytes(bytesToSend, sizeOfPacket);
                        delete[] bytesToSend;
                    }else if (blockNum == dataMapToSend.size()) {
                        dataMapToSend.clear();
                    }
                    break;
                }
//                LOGIN
                case 7: {
                    short blockNum = (static_cast<ACKPacket *>(packetFromServer))->getBlockNum();
                    if (blockNum == 0) {
                        (static_cast<ACKPacket *>(packetFromServer))->printACK();
                    } else {
                        std::cout << "Wrong Ack Block Number inside server listener" << std::endl;
                    }
                    break;
                }
                    //DELRQ
                case 8: {
                    short blockNum = (static_cast<ACKPacket *>(packetFromServer))->getBlockNum();
                    if (blockNum == 0) {
                        (static_cast<ACKPacket *>(packetFromServer))->printACK();
                    } else {
                        std::cout << "Wrong Ack Block Number inside server listener" << std::endl;
                    }
                    break;
                }
                    //DISC
                case 10: {
                    short blockNum = (static_cast<ACKPacket *>(packetFromServer))->getBlockNum();
                    if (blockNum == 0) {
                        (static_cast<ACKPacket *>(packetFromServer))->printACK();
                        _handler.shouldTerminate();
                    } else {
                        std::cout << "cant disconnect" << std::endl;
                    }
                    break;
                }
            }
            //todo check if you can do something while uploading

        }
            //ERROR
        case 5: {
            dynamic_cast<ERRORPacket *> (packetFromServer)->printError();

        }
            //BCAST
        case 9: {
            dynamic_cast<BCASTPacket *> (packetFromServer)->printMessage();
        }
    }
}

void ServerListener::shortToBytes(short num, char *bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void ServerListener::recievingData(std::vector<char> vector) {

}
