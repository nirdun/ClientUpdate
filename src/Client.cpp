#include <stdlib.h>
#include <iostream>
#include <boost/thread.hpp>
#include "../include/ConnectionHandler.h"
#include "../include/keyBoardListener.h"
#include "../include/ServerListener.h"



using namespace std;

int main(int argc, char *argv[]) {

    //192.168.56.1 7777
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);





    ConnectionHandler handler(host,port);
    keyBoardListener keyBoardListener(handler);
    ServerListener serverListener(handler);

    if (!handler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }



    boost::thread th1(&keyBoardListener::run, &keyBoardListener);
    boost::thread th2(&ServerListener::run, &serverListener);
//    th1.join();
//    th2.join();
    cout<<"Client is closed"<<endl;
    return 0;
}


