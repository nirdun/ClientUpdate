

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
        disconnectedReq = line == "DISC";
        if (!_handler.encodeAndSend(line)) {
            //todo check if should sync
            std::cout << "something went wrong whilee sending... \n" << std::endl;
            continue;
        }
// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        //todo delete prints

    }
}
