#include "connections/ConnManager.h"
#include <chrono>
#include <string>
#include <iostream>
#include "util/Settings.h"
#include "util/Dbg.h"
#include <exception>

using namespace std;

ConnManager::ConnManager(RoomManager& rm) : rm(rm) {
    DBG::sig("constructing ConnManager");
    newComesHandler = new thread(&ConnManager::tfunc, this);
    //	newComesHandler->join();
}

ConnManager::~ConnManager() {
    for (vector<Connection*>::iterator it = newComes.begin(); it != newComes.end(); ++it) {
        delete *it;
    }
    delete newComesHandler;
}

void ConnManager::addConnection(Connection* c) {
    DBG::sig("Adding connection to manager.");
    mqueue.lock();
    ncqueue.push_back(c);
    mqueue.unlock();
}

void ConnManager::tfunc() {
    while (true) {
        //DBG::sig("checking for msgs from connections");
        mutex.lock();
        if (rm.repChanged()) {
            rm.getRep(localRep);
        }
        string command;
        for (vector<Connection*>::iterator it = newComes.begin(); it != newComes.end();) {
            command = (*it)->getMsg();
            if (command == "") {
                continue;
            } else if (command == "hi") {
                //DBG::sig("Hello received");
                (*it)->sendMsg("hi");
            } else if (command == "rooms") {
                (*it)->sendMsg(localRep);
            } else if (command == "O status"){
		(*it)->sendMsg("handled by ConnManager");
	    }else if (command.substr(0, 4) == "join") {
		int roomId = -1;
                try {
                    roomId = stoi(command.substr(5, command.length() - 5));
                } catch (exception ex) {
                    DBG::sig("Connmanager exception while interpreting string: " + command);
                    (*it)->sendMsg("invalid room number");
		    //TODO warn connection for protocol error
                    continue;
                }
                int ret = rm.addToRoom(roomId, *it);
                if (ret == -1) {
                    (*it)->sendMsg("invalid room number " + to_string(roomId));
                } else if (ret == 1) {
                    (*it)->sendMsg("room full");
                } else if (ret == 2) {
                    (*it)->sendMsg("error while joining the room");
                } else if (ret == 0) {
                    (*it)->sendMsg("joined room " + to_string(roomId));
		    it = newComes.erase(it);
		    continue;
                }
            }/*else if (command ==) {

            }*/
            else {
                (*it)->sendMsg("sup");
		//TODO warn connection for protocol error
            }
	    ++it;
        }

        mqueue.lock();
        for (vector<Connection*>::iterator it = ncqueue.begin(); it != ncqueue.end(); ++it) {
            newComes.push_back((*it));
        }
        ncqueue.clear();
        mqueue.unlock();
        mutex.unlock();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void ConnManager::join() {
    newComesHandler->join();
}
