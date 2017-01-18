#pragma once

#include "BasePacket.h"
#include <string>


class LOGRQPacket : public BasePacket {

private:
    std::string userName;
public:
    wchar_t endByte = L'\0';

    LOGRQPacket();



     wchar_t getEndByte();

     void setEndByte(wchar_t endByte);

};
