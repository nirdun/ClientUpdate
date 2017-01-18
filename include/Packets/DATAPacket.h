#pragma once

#include "BasePacket.h"
#include <string>
#include <vector>
#include <iostream>
#include <string.h>

class DATAPacket : public BasePacket {
public:
    DATAPacket(std::vector<char> &bytes);

    DATAPacket(short opCode, short size, short block, char bytes[]);
    DATAPacket(short size, short block, char bytes[]);

    short getPacketSize();

    short getBlockNum();

    char* getData();


private:
    DATAPacket(char *bytes);

    char* data;
    short packetSize;
    short blockNum ;


};

