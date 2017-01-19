//
// Created by ניר דוניץ on 16.1.2017.
//


#include "../include/Packets/BasePacket.h"
#include "../include/Packets/ACKPacket.h"
#include "../include/Packets/ERRORPacket.h"
#include "../include/BidiEncoderDecoder.h"
#include "../include/Packets/BCASTPacket.h"


#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <string.h>
#include <iterator>
#include <algorithm>

using namespace std;

BidiEncoderDecoder::BidiEncoderDecoder() :
        _opCode(0),
        _block(0),
        _packetSize(0),
        _counterRead(0) {
    byteArr = std::vector<char>(1024);
    opCodeMap.clear();
    opCodeMap["RRQ"] = 1;
    opCodeMap["WRQ"] = 2;
    opCodeMap["DATA"] = 3;
    opCodeMap["ACK"] = 4;
    opCodeMap["ERROR"] = 5;
    opCodeMap["DIRQ"] = 6;
    opCodeMap["LOGRQ"] = 7;
    opCodeMap["DELRQ"] = 8;
    opCodeMap["BCAST"] = 9;
    opCodeMap["DISC"] = 10;
}

BasePacket *BidiEncoderDecoder::decodeBytes(char bytes[]) {

    _opCode = bytesToShort(bytes[0], bytes[1]);
    int length = sizeof(bytes);
    switch (_opCode) {
        //DATA
        case 3: {
            //todo - handle current action

            _packetSize = bytesToShort(bytes[2], bytes[3]);
            _block = bytesToShort(bytes[4], bytes[5]);
            return new DATAPacket(_opCode,
                                  _packetSize,
                                  _block,
                                  getPartOfByteArray(bytes, 6, sizeof(bytes)));
        }
            //ACK
        case 4: {
            _block = bytesToShort(bytes[2], bytes[3]);
            return new ACKPacket(_block);
        }
            //ERROR
        case 5: {

            short errCode = _packetSize = bytesToShort(bytes[2], bytes[3]);
            //length until 0.
            return new ERRORPacket(errCode, bytesToString(getPartOfByteArray(bytes, 4, length - 1)));
        }
            //BCAST
        case 9: {
            std::string fileName = bytesToString(getPartOfByteArray(bytes, 3, length - 1));
            return new BCASTPacket(bytes[2], fileName);

        }
        default:
            return nullptr;
    }

}


std::string BidiEncoderDecoder::bytesToString(char bytes[]) {
    return std::string(bytes);
}



char *BidiEncoderDecoder::getPartOfByteArray(char bytes[], int from, int to) {
    int size = to - from;
    char *newArray = new char[size];
    for (int i = from; i < to; i++) {
        newArray[i - from] = bytes[i];
    }
    return newArray;
}


void BidiEncoderDecoder::shortToBytes(short num, char *bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

std::vector<char> BidiEncoderDecoder::encodeInputTobytes(std::string line) {
    std::cout << "inside encodeInputTobytes"<<std::endl;


    std::cout << "after map"<<std::endl;

    std::vector<std::string> lineSplited;
    istringstream iss(line);
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         back_inserter(lineSplited));

//    std::cout <<lineSplited.at(0)<<"      "<<lineSplited.at(1)<<std::endl;

    char *bytes;
    char opCodeBytes[2];
    std::vector<char> bytesVec;

    vector<string>::iterator it;

    //line splited.at(0)
    it=lineSplited.begin();
    string request=it->data();

    it++;
    //line splited.at(1)
    string str=it->data();
    std::cout <<"after splited"<<std::endl;

    if(request=="RRQ"){
        this->fileName = str;

        shortToBytes(1, opCodeBytes);
        arrayToVector(&bytesVec,opCodeBytes,2);
        //inssert file name as chars
        std::copy(fileName.begin(), fileName.end(), std::back_inserter(bytesVec));


    }
    else if(request=="WRQ"){
        this->fileName = str;
//        bytes = new char[this->fileName.length() + 3];
        shortToBytes((short)2, opCodeBytes);
        arrayToVector(&bytesVec,opCodeBytes,2);
        std::copy(fileName.begin(), fileName.end(), std::back_inserter(bytesVec));
        bytesVec.push_back('\0');
    }else if(request=="ACK"){
        //todo disc shoult termintae
        shortToBytes((short)4, opCodeBytes);
        arrayToVector(&bytesVec,opCodeBytes,2);
        std::copy(str.begin(), str.end(), std::back_inserter(bytesVec));

    }else if(request=="DIRQ"){
        shortToBytes((short)6, opCodeBytes);
        arrayToVector(&bytesVec,opCodeBytes,2);

    }else if(request=="LOGRQ"){
        std::cout << "inside logrq"<<std::endl;
        shortToBytes((short)7, bytes);
        arrayToVector(&bytesVec,opCodeBytes,2);
        std::copy(str.begin(), str.end(), std::back_inserter(bytesVec));
        bytesVec.push_back('\0');
        std::cout << "end of logrq"<<std::endl;
    }else if(request=="DELRQ"){
        this->fileName = str;
        shortToBytes((short)8, opCodeBytes);
        arrayToVector(&bytesVec,opCodeBytes,2);
        std::copy(fileName.begin(), fileName.end(), std::back_inserter(bytesVec));
        bytesVec.push_back('\0');
    }else if(request=="DISC"){
        shortToBytes((short)6, opCodeBytes);
        arrayToVector(&bytesVec,opCodeBytes,2);

    }else{
        std::cout << "something wrong ---";

    }


//
//    switch (opCodeMap.at(lineSplited.at(0))) {
//        //RRQ
//        case 1:
//
//            this->fileName = lineSplited.at(1);
//            bytes = new char[this->fileName.length() + 3];
//            shortToBytes(1, bytes);
//            addStringToBytes(fileName, bytes, 2);
//            bytes[this->fileName.length() + 2] = '\0';
//            break;
//            //WRQ
//        case 2:
//            this->fileName = lineSplited.at(1);
//            bytes = new char[this->fileName.length() + 3];
//            shortToBytes(2, bytes);
//            addStringToBytes(fileName, bytes, 2);
//            bytes[this->fileName.length() + 2] = '\0';
//            break;
//        case 4:
//            bytes = new char[4];
//            shortToBytes(4, bytes);
//            addStringToBytes(lineSplited.at(1), bytes, 2);
//
//            break;
//            //DIRQ
//        case 6:
//            bytes = new char[2];
//            shortToBytes((short)6, bytes);
//            break;
//            //LOGRQ
//        case 7:
//        std::string use=lineSplited.at(1);
//            std::cout << "inside logrq"<<std::endl;
//
//            this->userName = lineSplited.at(1);
//            bytes = new char[this->userName.length() + 3];
//            shortToBytes(7, bytes);
//            addStringToBytes(userName, bytes, 2);
//            bytes[this->userName.length() + 2] = '\0';
//            std::cout << "inside logrq"<<std::endl;
//            break;
//            //DELRQ
//        case 8:
//            this->fileName = lineSplited.at(1);
//            bytes = new char[this->fileName.length() + 3];
//            shortToBytes(8, bytes);
//            addStringToBytes(fileName, bytes, 2);
//            bytes[this->fileName.length() + 2] = '\0';
//            break;
//            //DISC
//        case 10:
//            bytes = new char[2];
//            shortToBytes(6, bytes);
//            break;
//        default:
//            std::cout << "something wrong";
//
//
//    }
    return bytesVec;

}

void BidiEncoderDecoder::addStringToBytes(std::string str, char *bytes, int from) {
    char temp[str.size() + 1];
    strcpy(temp, str.c_str());
    for (int i = from; i - from < (sizeof(temp) / sizeof(*temp)); i++) {
        bytes[i] = temp[i - from];
    }
}

std::string BidiEncoderDecoder::getFileName() {
    return this->fileName;
}

void BidiEncoderDecoder::arrayToVector(std::vector<char> *v,char* arr,int size){
    for(int i=0;i<size;i++){
        (*v).push_back(arr[i]);
    }
}