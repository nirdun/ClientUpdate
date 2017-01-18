//
// Created by ניר דוניץ on 15.1.2017.
//

#ifndef CLIENT_KEYBOARDLISTENER_H
#define CLIENT_KEYBOARDLISTENER_H

#include <boost/thread.hpp>
#include "ConnectionHandler.h"

class KeyboardListener {
private:
    std::string _listenerType;
    ConnectionHandler &_handler;
    const short _bufferSize;



public:
    KeyboardListener(ConnectionHandler &handler);

    void run();

};

#include <iostream>
#include <boost/thread.hpp>


#endif //CLIENT_KEYBOARDLISTENER_H
