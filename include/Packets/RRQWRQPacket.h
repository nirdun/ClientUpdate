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

    virtual std::string getFileName();

    virtual void setFileName(const std::string &fileName);

    virtual wchar_t getEndByte();

    virtual void setEndByte(wchar_t endByte);

    virtual bool haveEndByte() override;
};
