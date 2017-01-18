#pragma once

#include "BasePacket.h"
#include <string>
#include <vector>
#include <iostream>


class DATAPacket : public BasePacket {
public:

    // field from zero to 512 bytes long.
private:
    DATAPacket(char *bytes);

    char* data;
    std::string fileName;
    short packetSize = 0;
    short blockNum = 0;

public:
    DATAPacket(std::vector<char> &bytes);

    DATAPacket(short opCode, short size, short block, char bytes[]);
    DATAPacket(short size, short block, char bytes[]);

    short getPacketSize();

     void setPacketSize(short packetSize);

     short getBlockNum();

     void setBlockNum(short blockNum);

    char* getData();

     void setData(std::vector<char> &data);

     std::string getFileName();

     void setFileName(const std::string &fileName);

    void printDirListing();
};

