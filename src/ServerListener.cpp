//
// Created by ניר דוניץ on 15.1.2017.
//


#include <boost/thread/pthread/thread_data.hpp>
#include "../include/ServerListener.h"
#include "../include/BidiEncoderDecoder.h"
#include "../include/Packets/BasePacket.h"
#include "../include/Packets/BCASTPacket.h"
#include "../include/Packets/ERRORPacket.h"
#include "../include/Packets/ACKPacket.h"
#include "../include/Packets/DATAPacket.h"
#include <fstream>
#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
using std::ifstream;
using std::ios;
using std::streampos;
using std::cout;
using std::endl;
using namespace std;

#include <iostream>
#include <boost/thread/thread.hpp>

ServerListener::ServerListener(ConnectionHandler &handler) :
        _handler(handler),
        _listenerType("server"), disconnedReq(false) {

}

void ServerListener::run() {
    BidiEncoderDecoder *encoderDecoder;
    while (!_handler.shouldTerminate() && !disconnedReq) {
        BasePacket *packetFromServer;

        packetFromServer = _handler.processServerPakect();
        createResponse(packetFromServer);

    }

}

void ServerListener::createResponse(BasePacket *packetFromServer) {
    short currentAct = _handler.getCurrentAction();
    switch (packetFromServer->getOpCode()) {
        //DATA
        case 3: {
            char *data = (static_cast<DATAPacket *>(packetFromServer))->getData();
            int size=(static_cast<DATAPacket *>(packetFromServer))->getPacketSize();
            for(int i=0;i<14;i++){
                std::cout<<data[i]<<std::endl;
            }
            dataFromServer.insert(dataFromServer.end(), data, data + size );

            int i = 0;
            for (std::vector<char>::iterator it = dataFromServer.begin(); it != dataFromServer.end(); ++it) {

                std::cout<< it.operator*()<<std::endl;
            }


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
                //dirc
            else if (currentAct == 6) {
                if (dataSize != 512) {
                    std::vector<char>::iterator it=dataFromServer.begin();
                    for(;it!=dataFromServer.end();it++){
                        if(it.operator*() =='\0'){
                            it.operator*()='\n';
                        }
                    }


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
                    //open "filename" read from it to map of vectors of chars and send first packet
                    std::ifstream stream;
                    stream.open(_handler.getFileName(), ios::in | ios::binary | ios::ate);
                    if (stream.is_open()) {
                        streampos fileSize = stream.tellg();
                        unsigned startFrom = (unsigned) (512 * blockNum);

                        if (startFrom < fileSize) {
                            stream.seekg(startFrom, ios::beg);
                            short leftToRead = (short) (((unsigned)fileSize - startFrom) < 512) ?
                                               ((unsigned)fileSize - startFrom) : 512;

                            char* dataBytes=new char[leftToRead];
                            stream.read(dataBytes, leftToRead);
                            stream.close();
                            char blockNumArr[2];
                            shortToBytes(blockNum + 1, blockNumArr);
                            char opCodeArr[2];
                            shortToBytes((short) 3, opCodeArr);
                            char leftToReadArr[2];
                            shortToBytes(leftToRead, leftToReadArr);
                            char dataBytesPacket[leftToRead+6];
                            _handler.mergeArrays(dataBytesPacket, opCodeArr, 2, 0);
                            _handler.mergeArrays(dataBytesPacket, leftToReadArr, 2, 2);
                            _handler.mergeArrays(dataBytesPacket, blockNumArr, 2, 4);
                            _handler.mergeArrays(dataBytesPacket, dataBytes, leftToRead, 6);
                            std::cout<<dataBytesPacket[15]<<std::endl;
                            _handler.sendBytes(dataBytesPacket, leftToRead + 6);
                            delete (dataBytes);
                        } else {
                            std::cout << "WRQ " << _handler.getFileName() << " complete" << std::endl;
                        }
                    }
                    else{
                        std::cout << "Failed to open: "<<_handler.getFileName() << std::endl;

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
                    disconnedReq = true;
                    break;
                }
            }
            break;
            //todo check if you can do something while uploading

        }
            //ERROR
        case 5: {
            static_cast<ERRORPacket *> (packetFromServer)->printError();
            break;

        }
            //BCAST
        case 9: {
            static_cast<BCASTPacket *> (packetFromServer)->printMessage();
            break;
        }
    }
}

void ServerListener::shortToBytes(short num, char *bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void ServerListener::recievingData(std::vector<char> vector) {

}
