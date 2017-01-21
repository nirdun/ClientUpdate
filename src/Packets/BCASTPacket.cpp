#include <iostream>
#include "../../include/Packets/BCASTPacket.h"


BCASTPacket::BCASTPacket(char addOrDelete, const std::string &filename):Filename(filename) {
    this->opCode = 9;
    this->fileAdded = addOrDelete == (short)1 ? true : false;

}

BCASTPacket::BCASTPacket(const std::string &filename):Filename(filename) {
    this->opCode = 9;

}

BCASTPacket::~BCASTPacket() {}
void BCASTPacket::printMessage() {
    std::string addOrdel = fileAdded ? "add" : "del";
    std::cout << "BCAST " << addOrdel << " " << Filename << std::endl;
}
