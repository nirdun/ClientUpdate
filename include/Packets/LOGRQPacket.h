#pragma once

#include "BasePacket.h"
#include <string>


class LOGRQPacket : public BasePacket {

private:
    std::string userName;
public:
    wchar_t endByte = L'\0';

    LOGRQPacket();

    virtual std::string getUserName();

    virtual void setUserName(const std::string &userName);

    virtual wchar_t getEndByte();

    virtual void setEndByte(wchar_t endByte);

    virtual bool haveEndByte() override;
};
