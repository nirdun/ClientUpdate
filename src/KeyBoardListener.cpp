

#include "../include/KeyBoardListener.h"



KeyBoardListener::KeyBoardListener(ConnectionHandler &handler):
        _listenerType("keyboard"),
        _handler(handler),
        _bufferSize(1024){
}

void KeyBoardListener::run() {

    while (!_handler.shouldTerminate()) {
        char buf[_bufferSize];
        std::cin.getline(buf, _bufferSize);
        std::string line(buf);
        int len = line.length();
        if (!_handler.encodeAndSend(line)) {
            //todo check if should sync
            std::cout << "something went wrong while sending... \n" << std::endl;
            continue;
        }
// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        //todo delete prints
        std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;

    }
}
