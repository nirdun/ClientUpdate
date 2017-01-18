#include <iostream>
#include "../../include/Packets/ACKPacket.h"


ACKPacket::ACKPacket() {
    this->opCode = 4;
    this->blockNum = 0;
}

ACKPacket::ACKPacket(short blockNum) {
    this->opCode = 4;
    this->blockNum = blockNum;
}

short ACKPacket::getBlockNum() {
    return blockNum;
}

void ACKPacket::printACK() {
    std::cout << "ACK " << blockNum << std::endl;
}
