#pragma once

#include "BasePacket.h"
#include <string>
#include <vector>


class DELRQPacket : public BasePacket {
public:
    std::string fileName;
    wchar_t endByte = L'\0';

    DELRQPacket(std::vector<char> &bytes);

    DELRQPacket(const std::string &fileName);



};
