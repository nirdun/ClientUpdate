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

     bool haveEndByte();

     void setOpCode(short opCode);
};