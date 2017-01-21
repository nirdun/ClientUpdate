#pragma once

#include "BasePacket.h"


class ACKPacket : public BasePacket {
private:
    short blockNum ;

public:
    ACKPacket();


    ACKPacket(short blockNum);

     short getBlockNum();

    void printACK();
    virtual ~ACKPacket();
};
