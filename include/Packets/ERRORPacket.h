#pragma once

#include "BasePacket.h"
#include <string>

class ERRORPacket : public BasePacket {
private:
    std::string ErrMsg;
    short endByte = 0;
    short ErrorCode = 0;

    void difineErrMsg();

public:
    ERRORPacket(short errorType);

    ERRORPacket(short errorType, const std::string &errMsg);

    std::string getErrMsg();

    void setErrMsg(const std::string &errMsg);

    short getEndByte();

    void setEndByte(short endByte);

    int getErrorType();

    void setErrorType(short errorType);

    short getErrorCode();

    void setErrorCode(short errorCode);

    void printError();

};