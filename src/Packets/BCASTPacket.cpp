#include <iostream>
#include "../../include/Packets/BCASTPacket.h"


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



void BCASTPacket::printMessage() {
    std::string addOrdel = fileAdded ? "add" : "del";
    std::cout << "BCAST " << addOrdel << " " << Filename << std::endl;
}
