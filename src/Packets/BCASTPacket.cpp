#include <iostream>
#include "../../include/Packets/BCASTPacket.h"


BCASTPacket::BCASTPacket(std::vector<char> &bytes) {
    this->opCode = 9;
    bytyarr = bytes;

}

BCASTPacket::BCASTPacket(char addOrDelete, const std::string &filename) {
    this->opCode = 9;
    this->fileAdded = addOrDelete == '1' ? true : false;
    this->Filename = filename;

}

BCASTPacket::BCASTPacket(const std::string &filename) {
    this->opCode = 9;
    this->Filename = filename;

}

std::string BCASTPacket::getFileName() {
    return Filename;
}

void BCASTPacket::setFilename(const std::string &filename) {
    Filename = filename;
}

bool BCASTPacket::isFileAdded() {
    return fileAdded;
}

void BCASTPacket::setFileAdded(bool fileAdded) {
    this->fileAdded = fileAdded;
}

bool BCASTPacket::haveEndByte() {
    return true;
}

void BCASTPacket::printMessage() {
    std::string addOrdel = fileAdded ? "add" : "del";
    std::cout << "BCAST " << addOrdel << " " << Filename << std::endl;
}
