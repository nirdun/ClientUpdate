#pragma once

#include "BasePacket.h"
#include <string>
#include <vector>
#include <iostream>
#include <string.h>

class DATAPacket : public BasePacket {
public:

    DATAPacket(short opCode, short size, short block, char bytes[]);
    DATAPacket(short size, short block, char bytes[]);

    short getPacketSize();

    short getBlockNum();

    char* getData();


private:
    char* data;
    short packetSize;
    short blockNum ;


};

