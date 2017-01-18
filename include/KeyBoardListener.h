//
// Created by ניר דוניץ on 15.1.2017.
//

#ifndef CLIENT_KeyBoardListener_H
#define CLIENT_KeyBoardListener_H

#include <boost/thread.hpp>
#include "ConnectionHandler.h"

class KeyBoardListener {
private:
    std::string _listenerType;
    ConnectionHandler &_handler;
    const short _bufferSize;



public:
    KeyBoardListener(ConnectionHandler &handler);

    void run();

};

#include <iostream>
#include <boost/thread.hpp>


#endif //CLIENT_KeyBoardListener_H
