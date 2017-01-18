#pragma once

#include "BasePacket.h"


class ACKPacket : public BasePacket {
private:
    short blockNum = 0;

public:
    ACKPacket();


    ACKPacket(short blockNum);

    virtual short getBlockNum();

    void printACK();
};
