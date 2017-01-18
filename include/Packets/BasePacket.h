#pragma once

#include <vector>

class BasePacket {
protected:
    short opCode = 0;
    std::vector<char> bytyarr;
public:
    virtual short getOpCode();

    BasePacket(std::vector<char> &bytes);

    BasePacket();

    virtual bool haveEndByte();

    virtual void setOpCode(short opCode);
};