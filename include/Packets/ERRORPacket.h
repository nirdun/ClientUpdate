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
    virtual bool haveEndByte() override;


    virtual std::string getErrMsg();

    virtual void setErrMsg(const std::string &errMsg);

    virtual short getEndByte();

    virtual void setEndByte(short endByte);

    virtual int getErrorType();

    virtual void setErrorType(short errorType);

    virtual short getErrorCode();

    virtual void setErrorCode(short errorCode);

    void printError();
};