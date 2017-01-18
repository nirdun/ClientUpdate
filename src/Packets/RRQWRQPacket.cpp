#include "../../include/Packets/RRQWRQPacket.h"

RRQWRQPacket::RRQWRQPacket(std::vector<char> &bytes, short opCode, const std::string &fileName) {
    this->opCode = opCode;
    this->bytyarr = bytes;
    this->fileName = fileName;

}

std::string RRQWRQPacket::getFileName() {
    return fileName;
}

void RRQWRQPacket::setFileName(const std::string &fileName) {
    this->fileName = fileName;
}

wchar_t RRQWRQPacket::getEndByte() {
    return endByte;
}

void RRQWRQPacket::setEndByte(wchar_t endByte) {
    this->endByte = endByte;
}

