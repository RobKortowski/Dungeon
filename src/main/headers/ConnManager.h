#ifndef CONNMANAGER_H
#define CONNMANAGER_H

#include "Connection.h"
#include "Interpreter.h"
#include "RoomManager.h"

#include <vector>
#include <thread>
#include <mutex>
#include <string>

class ConnManager {
public:
    ConnManager(RoomManager&);
    ~ConnManager();
    void addConnection(Connection*);
    void join();

private:
    RoomManager& rm;
    std::string localRep;
    
    std::mutex mutex; //access to newComes
    std::vector<Connection*> newComes;

    std::mutex mqueue;
    std::vector<Connection*> ncqueue;
    
    std::thread* newComesHandler;
    //Interpreter interpreter;
    void tfunc();
};

#endif
