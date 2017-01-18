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

    virtual void setPacketSize(short packetSize);

    virtual short getBlockNum();

    virtual void setBlockNum(short blockNum);

    char* getData();

    virtual void setData(std::vector<char> &data);

    virtual std::string getFileName();

    virtual void setFileName(const std::string &fileName);

    void printDirListing();
};

