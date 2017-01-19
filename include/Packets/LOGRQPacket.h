#pragma once

#include "BasePacket.h"
#include <string>


class LOGRQPacket : public BasePacket {

private:
    std::string userName;
public:

    LOGRQPacket();


};
