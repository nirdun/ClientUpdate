#pragma once

#include "BasePacket.h"
#include <string>
#include <vector>


/// <summary>
/// Created by Nirdun on 9.1.2017.
/// </summary>
class RRQWRQPacket : public BasePacket {
public:
    std::string fileName;
    wchar_t endByte = L'\0';

    RRQWRQPacket(std::vector<char> &bytes, short opCode, const std::string &fileName);

     std::string getFileName();

     void setFileName(const std::string &fileName);

     wchar_t getEndByte();

     void setEndByte(wchar_t endByte);

     bool haveEndByte() override;
};
