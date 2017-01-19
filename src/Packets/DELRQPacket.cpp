#include <vector>
#include <string>
#include "../../include/Packets/DELRQPacket.h"


DELRQPacket::DELRQPacket() {
    this->opCode = 8;
}

DELRQPacket::DELRQPacket(const std::string &fileName) {
    this->opCode = 8;
    this->fileName = fileName;
}
