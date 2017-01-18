#include "../../include/Packets/DATAPacket.h"

DATAPacket::DATAPacket(short size, short block, char *bytes) {
    this->opCode = 3;
    this->data = bytes;
    this->blockNum=block;
    this->packetSize=size;
}

DATAPacket::DATAPacket(short opCode, short size, short block, char* bytes) {
    this->opCode = opCode;
    this->data = bytes;
    this->blockNum=block;
    this->packetSize=size;
}

short DATAPacket::getPacketSize() {
    return packetSize;
}


short DATAPacket::getBlockNum() {
    return blockNum;
}



char* DATAPacket::getData() {
    //todo - clone?
    return data;
}


