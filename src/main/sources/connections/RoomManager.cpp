/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RoomManager.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on February 19, 2017, 9:37 PM
 */

#include "connections/RoomManager.h"
#include "util/Dbg.h"
#include <sstream>
#include <chrono>

using namespace std;

RoomManager::RoomManager(int roomCount) : roomCount(roomCount), changed(false){
    for (int i = 0; i < roomCount; ++i) {
        Room* r = new Room(i);
        rooms.push_back(r);
        pInfos.push_back(new publicInfo(i));
    }
    for (Room* r : rooms) {
        r->start();
    }
    updater = new thread(&RoomManager::pInfosUpdater, this);
}

RoomManager::RoomManager(const RoomManager& orig) {
}

RoomManager::~RoomManager() {
}

bool RoomManager::repChanged() {
    return changed;
}

void RoomManager::getRep(string& toUpdate){
    repProt.lock();
    toUpdate = infoRep;
    repProt.unlock();
    changed = false;
    //DBG::sig("Representation string copied.");
}

void RoomManager::pInfosUpdater() {
    vector<Room*>::iterator it;
    vector<publicInfo*>::iterator it2;
    ostringstream oss;
    publicInfo* tmp;
    while (true) {
        for (it = rooms.begin(), it2 = pInfos.begin(); it != rooms.end(); ++it, ++it2) {
	    (*it)->updateMe(**it2);
        }
	oss.str("");
	tmp = pInfos.front();
	oss << tmp->roomId << "$" << tmp->playersCount << "$" << tmp->maxPlayers;
	for(it2 = pInfos.begin() + 1; it2 < pInfos.end(); ++it2){
	    oss << "$" << (*it2)->roomId << "$" << 
		    (*it2)->playersCount << "$" << (*it2)->maxPlayers; 
	}
	repProt.lock();
	infoRep = oss.str();
	repProt.unlock();
	changed = true;
	//DBG::sig("Infos updated.");
	this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int RoomManager::addToRoom(int i, Connection* c){
    if(i < 0 || i >= roomCount){
	return -1;
    }else{
	return rooms.at(i)->addConnection(c);
    }
}


