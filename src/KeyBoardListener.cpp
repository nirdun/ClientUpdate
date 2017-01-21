

#include "../include/KeyBoardListener.h"


KeyBoardListener::KeyBoardListener(ConnectionHandler &handler) :
        _handler(handler),
        _bufferSize(1024),disconnectedReq(false) {
}

void KeyBoardListener::run() {

    while (!_handler.shouldTerminate() && !disconnectedReq) {

        char buf[_bufferSize];
        std::cin.getline(buf, _bufferSize);

        std::string line(buf);
        if (!_handler.encodeAndSend(line)) {
            //todo check if should sync
            continue;
        }
        if(_handler.isLoggedIn()){
            disconnectedReq = line == "DISC";

        }
// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        //todo delete prints

    }
}
