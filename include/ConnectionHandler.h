
#pragma once
#ifndef CLIENT_CONNECTIONHANDLER_H
#define CLIENT_CONNECTIONHANDLER_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <map>
#include "Packets/BasePacket.h"
#include "BidiEncoderDecoder.h"

using boost::asio::ip::tcp;

class ConnectionHandler {
private:
    std::string _host;
    short _port;
    short _currentAction;
    bool _connected;
    const std::string host_;
    const short port_;
    boost::asio::io_service io_service_;   // Provides core I/O functionality
    tcp::socket socket_;
    //std::map <std::string, int> _currentActionMap;
    BidiEncoderDecoder* encoderDecoder;
    std::map<std::string,short >currentActionMap;

public:
    ConnectionHandler(ConnectionHandler& connectionHandler);
    std::string getHost();
    short getPort();

    std::string getFileName();
    ConnectionHandler(const ConnectionHandler &handler);
    void setCurrentAction(short currentAction);
    short getCurrentAction() ;
    //int getCurrentActionNum(std::string currentAction);

    ConnectionHandler(std::string host, short port);

    bool shouldTerminate();
    bool encodeAndSend(std::string line);
    void mergeArrays(char* insertTo,char *insertFrom,int sizeOfInsertFrom,int from);


    BasePacket *processServerPakect();

    void terminate();

     ~ConnectionHandler();

    // Connect to the remote machine
    bool connect();

    // Read a fixed number of bytes from the server - blocking.
    // Returns false in case the connection is closed before bytesToRead bytes can be read.
    bool getBytes(char bytes[], unsigned int bytesToRead);

    // Send a fixed number of bytes from the client - blocking.
    // Returns false in case the connection is closed before all the data is sent.
    bool sendBytes(const char bytes[], int bytesToWrite);

    // Read an ascii line from the server
    // Returns false in case connection closed before a newline can be read.
    bool getLine(std::string& line);

    // Send an ascii line from the server
    // Returns false in case connection closed before all the data is sent.
    bool sendLine(std::string& line);

    // Get Ascii data from the server until the delimiter character
    // Returns false in case connection closed before null can be read.
    bool getFrameAscii(std::string& frame, char delimiter);

    // Send a message to the remote host.
    // Returns false in case connection is closed before all the data is sent.
    bool sendFrameAscii(const std::string& frame, char delimiter);

    // Close down the connection properly.
    void close();


    std::vector<char>getBytesUntilDelimeter();

    void updateCurrentAction(char *bytes);
};


#endif //CLIENT_CONNECTIONHANDLER_H
