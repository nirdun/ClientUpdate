

#include "../include/KeyBoardListener.h"


KeyBoardListener::KeyBoardListener(ConnectionHandler &handler) :
        _listenerType("keyboard"),
        _handler(handler),
        _bufferSize(1024),disconnedReq(false) {
    std::cout << "c_tor keyboard listener" << std::endl;

}

void KeyBoardListener::run() {

    while (!_handler.shouldTerminate() && !disconnedReq) {

        char buf[_bufferSize];
        std::cin.getline(buf, _bufferSize);
        std::cout << "after get line" << std::endl;

        std::string line(buf);
        disconnedReq = line == "DISC";
        if (!_handler.encodeAndSend(line)) {
            //todo check if should sync
            std::cout << "something went wrong whilee sending... \n" << std::endl;
            continue;
        }
// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        //todo delete prints

    }
}
