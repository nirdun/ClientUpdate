//
// Created by ניר דוניץ on 15.1.2017.
//
#pragma once
#ifndef CLIENT_SERVERLISTENER_H
#define CLIENT_SERVERLISTENER_H

#include <boost/thread.hpp>

#include "ConnectionHandler.h"

class ServerListener {
private:

    std::string _listenerType;
    ConnectionHandler &_handler;
    std::vector<char> dataFromServer;
    void shortToBytes(short num, char *bytesArr);
    std::map<int,std::vector<char> > dataMapToSend;
    bool disconnedReq;
public:
    ServerListener(ConnectionHandler& handler);
    void run();

    void createResponse(BasePacket *packet);

    void recievingData(std::vector<char> vector);
};








#endif //CLIENT_SERVERLISTENER_H
