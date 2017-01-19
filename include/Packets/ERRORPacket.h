#pragma once

#include "BasePacket.h"
#include <string>

class ERRORPacket : public BasePacket {
private:
    std::string ErrMsg;
    short ErrorCode;

    void difineErrMsg();

public:
    ERRORPacket(short errorType);

    ERRORPacket(short errorType, const std::string &errMsg);


    void printError();

};