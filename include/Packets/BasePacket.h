#pragma once

#include <vector>

class BasePacket {
protected:
    short opCode = 0;
    std::vector<char> bytyarr;
public:
     short getOpCode();

    BasePacket(std::vector<char> &bytes);

    BasePacket();

    BasePacket(const BasePacket&);
     void setOpCode(short opCode);
};