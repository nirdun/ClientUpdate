//
// Created by ניר דוניץ on 16.1.2017.
//
#pragma once
#ifndef BIDIENCODERDECODER_H
#define BIDIENCODERDECODER_H


#include <map>
#include "Packets/BasePacket.h"
#include "Packets/DIRQPacket.h"
#include "Packets/DATAPacket.h"
#include "Packets/ERRORPacket.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

class BidiEncoderDecoder {
private:
    short _opCode;
    short _packetSize;
    short _block;
    int _counterRead;
    std::vector<char> byteArr;
    std::string fileName;


    std::map<std::string, short> opCodeMap;

    void mergeArrays(char* insertTo,char *insertFrom,int from);

    DATAPacket *createDataPacket();

//    static Set<int> *const haveEndByte = std::unordered_set<int>(Arrays::asList(1,1 2, 5, 7, 8, 9));
    std::vector<char> encode(BasePacket *packet);

    std::vector<char> encodeDataPacket(DATAPacket *dpacket);
    void shortToBytes(short num, char *bytesArr);
    std::vector<char> encodeERROR(ERRORPacket *dpacket);
    char * getPartOfByteArray(char bytes[], int from, int to);


public:
    BidiEncoderDecoder();
    std::string getFileName();
    void vectorToArray(std::vector<char> vector,char *arr);
    BasePacket *decodeBytes(char* bytes,int lengthOfArray);

    short getOpCode(char a, char b);

    short bytesToShort(char a, char b);

    std::string bytesToString(char *bytes);
    void arrayToVector(std::vector<char> *v,char* arr,int size);
    std::vector<char> encodeInputTobytes(std::string line);

//    void addStringToBytes(std::string basic_string, char bytes[], int i);
};

#endif //BIDIENCODERDECODER_H
