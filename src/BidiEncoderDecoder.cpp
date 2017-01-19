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

char *BidiEncoderDecoder::encodeInputTobytes(std::string line) {
    std::cout << "inside encodeInputTobytes"<<std::endl;


    std::cout << "after map"<<std::endl;

    std::vector<std::string> lineSplited;
    istringstream iss(line);
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         back_inserter(lineSplited));

//    std::cout <<lineSplited.at(0)<<"      "<<lineSplited.at(1)<<std::endl;

    char *bytes;

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
        bytes = new char[this->fileName.length() + 3];
        shortToBytes(1, bytes);
        addStringToBytes(fileName, bytes, 2);
        bytes[this->fileName.length() + 2] = '\0';
    }
    else if(request=="WRQ"){
        this->fileName = str;
        bytes = new char[this->fileName.length() + 3];
        shortToBytes(2, bytes);
        addStringToBytes(fileName, bytes, 2);
        bytes[this->fileName.length() + 2] = '\0';
    }else if(request=="ACK"){
        //todo disc shoult termintae
        bytes = new char[4];
        shortToBytes(4, bytes);
        addStringToBytes(str, bytes, 2);

    }else if(request=="DIRQ"){
        bytes = new char[2];
        shortToBytes((short)6, bytes);
    }else if(request=="LOGRQ"){
        std::cout << "inside logrq"<<std::endl;
        bytes = new char[str.length() + 3];
        shortToBytes(7, bytes);
        addStringToBytes(str, bytes, 2);
        bytes[str.length() + 2] = '\0';
        std::cout << "end of logrq"<<std::endl;
    }else if(request=="DELRQ"){
        this->fileName = str;
        bytes = new char[this->fileName.length() + 3];
        shortToBytes(8, bytes);
        addStringToBytes(fileName, bytes, 2);
        bytes[this->fileName.length() + 2] = '\0';
    }else if(request=="DISC"){
        bytes = new char[2];
        shortToBytes(6, bytes);

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
    return bytes;

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







//
////BidiEncoderDecoder::BidiEncoderDecoder():
////_opCode(0){
////    counterRead = 0;
////    this->opCode = opCode;
////    byteArr = std::vector<char>(1024); // todo size?
////}
////
////BasePacket* BidiEncoderDecoder::decodeNextByte(char nextByte){
////        byteArr[counterRead] = nextByte;
////        counterRead++;
////        BasePacket *packet = nullptr;
////    std::set<short > haveEndByte={1,2,4};
////    std::set<short >::iterator it;
////
////
////
////        //initialize op code.
////        if (counterRead == 2) {
////            opCode = byteArr[0]);
////
////            // directory listing
////            if (opCode == 6) {
////                return new DIRQPacket();
////            } else if (opCode == 10) {
////                //disconnect
////                return new DISCPacket();
////            }
////        }
////    it=haveEndByte.find(opCode);
////        if ( it!=&& opCode != 0) {
////            if (opCode == 4) {
////                return new ACKPacket();
////            } else if (opCode == 3) {
////                packet = createDataPacket();
////            }
////        } else if (!shouldContinueRead(nextByte) && opCode != 0) {
////            packet = createPacket(opCode, byteArr);
////        }
////        return packet;
////    }
////
////    DATAPacket* BidiEncoderDecoder:: createDataPacket() {
////        DATAPacket *dPacket = nullptr;
////        // make a one bigger
////
////
////        if (counterRead == 4) {
////            //size of data and first six bytes.
////            packetSize = bytesToShort(byteArr) + 6;
////        } else if (counterRead == packetSize) {
////            //todo divide packet
////            dPacket = new DATAPacket(Arrays::copyOf(byteArr, packetSize));
////        }
////
////        return dPacket;
////    }
////
////     BasePacket *createPacket(short opCode, std::vector<char> &bytes) {
////        BasePacket *packet = nullptr;
////        switch (opCode) {
////            //Read request.
////            case 1: {
////                std::string fileNameWRQ = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
////                packet = new RRQWRQPacket(bytes, opCode, fileNameWRQ);
////                std::string fileName = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
////                (static_cast<RRQWRQPacket *>(packet))->setFileName(fileName);
////
////
////                break;
////                //Write request
////            }
////            case 2: {
////                std::string fileNameRRQ = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
////                packet = new RRQWRQPacket(bytes, opCode, fileNameRRQ);
////                break;
////                //Error request.
////            }
////            case 5: {
////                //todo - check if insert err msg different from value code optional
////                int errorCode = bytesToShort(Arrays::copyOfRange(bytes, 2, 4));
////                packet = new ERRORPacket(static_cast<short>(errorCode));
////                break;
////                //Login request
////            }
////            case 7: {
////                packet = new LOGRQPacket();
////                std::string userName = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
////                (static_cast<LOGRQPacket *>(packet))->setUserName(userName);
////
////                break;
////                //Delete request
////            }
////            case 8: {
////                std::string fileNameDelrq = bytesArrToString((Arrays::copyOfRange(bytes, 2, counterRead - 1)));
////                packet = new DELRQPacket(fileNameDelrq);
////                break;
////                //Broadcast request
////            }
////            case 9: {
////                std::string fileNameBcast = bytesArrToString((Arrays::copyOfRange(bytes, 3, counterRead - 1)));
////                packet = new BCASTPacket(bytes, static_cast<short>(bytes[2]), fileNameBcast);
////                break;
////            }
////            default:
////                std::cout << std::string(L"Wrong OpCode") << std::endl;
////        }
////        return packet;
////    }
////
////
////     std::string bytesArrToString(std::vector<char> &bytes) {
////        //notice that we explicitly requesting that the string will be decoded from UTF-8
////        //this is not actually required as it is the default encoding in java.
////        std::string result = std::string(bytes, 0, bytes.size(), StandardCharsets::UTF_8);
////        return result;
////    }
////
////    //return true if finish byte-0 is reading
////private:
////    bool shouldContinueRead(char nextByte) {
////        return (nextByte != 0);
////    }
//std::vector<char>BidiEncoderDecoder:: encode(BasePacket *message){
//        opCode = message->getOpCode();
//        switch (opCode) {
//            //todo : should be more packets? example DELRQ ?
//            case 3:
//                byteArr = encodeDataPacket(static_cast<DATAPacket *>(message));
//                break;
//            case 4:
//                byteArr = encodeACK(static_cast<ACKPacket *>(message));
//                break;
//            case 5:
//                byteArr = encodeERROR(static_cast<ERRORPacket *>(message));
//                break;
//            case 9:
//                byteArr = encodeBCAST(static_cast<BCASTPacket *>(message));
//                break;
//            default:
//                std::cout << std::string(L"Wrong OpCode") << std::endl;
//        }
//        return byteArr;
//    }
//
//std::vector<char> BidiEncoderDecoder::encodeDataPacket(DATAPacket *dpacket){
//        short packetSize = dpacket->getPacketSize();
//
//        //todo - check id bytes ok
//        std::cout << std::string(L"size of data packet in encodeDataPacket fun : ") << packetSize << std::endl;
//        std::vector<char> opCodeByte = shortToBytes(opCode);
//        std::vector<char> packetSizeBytes = shortToBytes(packetSize);
//        std::vector<char> blockNumberBytes = shortToBytes(dpacket->getBlockNum());
//        return mergeArrays({opCodeByte, packetSizeBytes, blockNumberBytes, dpacket->getData()});
//    }
//
//
//
////     std::vector<char> encodeACK(ACKPacket *packet) {
////        std::vector<char> opCodeByte = shortToBytes(opCode);
////        std::vector<char> blockBytes = shortToBytes(packet->getBlockNum());
////
////        //todo delete comments
////        //        System.arraycopy(opCodeByte, 0, bytes, 0, opCodeByte.length);
////        //        System.arraycopy(blockBytes, 0, bytes, opCodeByte.length, blockBytes.length);
////        return mergeArrays({opCodeByte, blockBytes});
////    }
//
//        std::vector<char> BidiEncoderDecoder::encodeERROR(ERRORPacket *dpacket){
////        std::vector<char> opCodeByte = shortToBytes(opCode);
//            char opcode2=dpacket->getOpCode();
//            char errorCode=dpacket->getErrorCode();
////        std::vector<char> errorCode = shortToBytes(packet->getErrorCode());
////        std::vector<char> errorMsg;
//            char *encodeErr=new char[dpacket->getErrMsg().size()+1];
//            a[dpacket->getErrMsg().size()]=0;
//            memcpy(a,dpacket->getErrMsg().c_str(),s.size());
//        try {
//            errorMsg = packet->getErrMsg().getBytes("UTF-8");
//        }
//        catch (const UnsupportedEncodingException &e) {
//            e->printStackTrace();
//        }
//
//
//        return mergeArrays({opCodeByte, errorCode, errorMsg, endByte});
//
//
//     short getOpCode(std::vector<char> &byteArr) {
//        short result = static_cast<short>((byteArr[0] & 0xff) << 8);
//        result += static_cast<short>(byteArr[1] & 0xff);
//        return result;
//    }
//
//     std::vector<char> shortToBytes(short num) {
//        std::vector<char> bytesArr(2);
//        bytesArr[0] = static_cast<char>((num >> 8) & 0xFF);
//        bytesArr[1] = static_cast<char>(num & 0xFF);
//        return bytesArr;
//    }
//
//
//     short bytesToShort(std::vector<char> &byteArr) {
//        short result = static_cast<short>((byteArr[0] & 0xff) << 8);
//        result += static_cast<short>(byteArr[1] & 0xff);
//        return result;
//    }
//
//
//    /// <summary>
//    /// merge multiple byre arrays to one array.
//    /// </summary>
//    /// <param name="arrays"> is byte arrays. </param>
//    /// <returns> merged Array. </returns>
//    //todo check if private?
//    static std::vector<char> mergeArrays(std::vector<char> &arrays) {
//        // Count the number of arrays passed for merging and the total size of resulting array
//        int arrCount = 0;
//        int count = 0;
//        for (char[] array_Renamed :
//            arrays)
//        {
//            arrCount++;
//            count += array_Renamed.size();
//        }
//        std::cout << std::string(L"Arrays passed for merging : ") << arrCount << std::endl;
//        std::cout << std::string(L"Array size of resultig array : ") << count << std::endl;
//
//        // Create new array and copy all array contents
//        int start = 0;
//        std::vector<char> mergedArray(count);
//        for (char[] array_Renamed :
//            arrays)
//        {
//            System::arraycopy(array_Renamed, 0, mergedArray, start, array_Renamed.size());
//            start += array_Renamed.size();
//        }
//        return mergedArray;
//    }
//
//
