#pragma once

#include "BasePacket.h"
#include <string>


class LOGRQPacket : public BasePacket {

private:
    std::string userName;
public:
    wchar_t endByte = L'\0';

    LOGRQPacket();

     std::string getUserName();

     void setUserName(const std::string &userName);

     wchar_t getEndByte();

     void setEndByte(wchar_t endByte);

     bool haveEndByte() override;
};
