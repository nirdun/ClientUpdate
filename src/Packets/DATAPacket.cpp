#include "../../include/Packets/DATAPacket.h"


DATAPacket::DATAPacket(char* bytes) {
    this->opCode = 3;
    this->data = bytes;
    this->setPacketSize(static_cast<short>(strlen(data)));
}

DATAPacket::DATAPacket(short size, short block, char *bytes) {
    this->opCode = 3;
    this->data = bytes;
    setBlockNum(block);
    this->setPacketSize(static_cast<short>(strlen(data)));
}

DATAPacket::DATAPacket(short opCode, short size, short block, char* bytes) {
    this->opCode = opCode;
    this->data = bytes;
    setBlockNum(block);
    this->setPacketSize(static_cast<short>(strlen(data)));
}

short DATAPacket::getPacketSize() {
    return packetSize;
}

void DATAPacket::setPacketSize(short packetSize) {
    this->packetSize = packetSize;
}

short DATAPacket::getBlockNum() {
    return blockNum;
}

void DATAPacket::setBlockNum(short blockNum) {
    this->blockNum = blockNum;
}


char* DATAPacket::getData() {
    //todo - clone?
    return data;
}

std::string DATAPacket::getFileName() {
    return fileName;
}

void DATAPacket::setFileName(const std::string &fileName) {
    this->fileName = fileName;
}

void DATAPacket::printDirListing() {

}
