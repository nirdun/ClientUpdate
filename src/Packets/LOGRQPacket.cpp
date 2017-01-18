#include "../../include/Packets/LOGRQPacket.h"

LOGRQPacket::LOGRQPacket() {
    this->opCode = 7;

}


wchar_t LOGRQPacket::getEndByte() {
    return endByte;
}

void LOGRQPacket::setEndByte(wchar_t endByte) {
    this->endByte = endByte;
}
