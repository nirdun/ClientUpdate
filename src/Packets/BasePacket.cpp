#include "../../include/Packets/BasePacket.h"


short BasePacket::getOpCode() {
    return opCode;
}

BasePacket::BasePacket(std::vector<char> &bytes) {
    this->bytyarr = bytes;
}

BasePacket::BasePacket() {
    bytyarr = std::vector<char>(0);
}
BasePacket::BasePacket(const BasePacket& basePacket){
    opCode=basePacket.opCode;
}

void BasePacket::setOpCode(short opCode) {
    this->opCode = opCode;
}
