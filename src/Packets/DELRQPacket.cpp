#include <vector>
#include <string>
#include "../../include/Packets/DELRQPacket.h"


DELRQPacket::DELRQPacket(std::vector<char> &bytes) {
    this->opCode = 8;
    bytyarr = bytes;
}

DELRQPacket::DELRQPacket(const std::string &fileName) {
    this->opCode = 8;
    this->fileName = fileName;
}
