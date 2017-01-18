#pragma once

#include "BasePacket.h"
#include <string>

class ERRORPacket : public BasePacket {
private:
    std::string ErrMsg;
    short endByte = 0;
    short ErrorCode = 0;

public:
    ERRORPacket(short errorType);

    ERRORPacket(short errorType, const std::string &errMsg);

private:
    void difineErrMsg();

public:
     bool haveEndByte() override;


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