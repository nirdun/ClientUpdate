#include "../../include/Packets/LOGRQPacket.h"

LOGRQPacket::LOGRQPacket() {
    this->opCode = 7;

}

std::string LOGRQPacket::getUserName() {
    return userName;
}

void LOGRQPacket::setUserName(const std::string &userName) {
    this->userName = userName;
}

wchar_t LOGRQPacket::getEndByte() {
    return endByte;
}

void LOGRQPacket::setEndByte(wchar_t endByte) {
    this->endByte = endByte;
}

bool LOGRQPacket::haveEndByte() {
    return true;
}