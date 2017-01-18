//
// Created by ניר דוניץ on 15.1.2017.
//

#ifndef CLIENT_keyBoardListener_H
#define CLIENT_keyBoardListener_H

#include <boost/thread.hpp>
#include "ConnectionHandler.h"

class keyBoardListener {
private:
    std::string _listenerType;
    ConnectionHandler &_handler;
    const short _bufferSize;



public:
    keyBoardListener(ConnectionHandler &handler);

    void run();

};

#include <iostream>
#include <boost/thread.hpp>


#endif //CLIENT_keyBoardListener_H
