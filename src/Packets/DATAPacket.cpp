#include "../../include/Packets/DATAPacket.h"

DATAPacket::DATAPacket(short size, short block, char *bytes):data(bytes),blockNum(block),packetSize(size) {
    this->opCode = 3;
}

DATAPacket::DATAPacket(short opCode, short size, short block, char* bytes):data(bytes),
                                                                           blockNum(block),packetSize(size) {
    this->opCode = opCode;
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
DATAPacket::~DATAPacket() {}