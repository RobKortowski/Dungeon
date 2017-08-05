/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Room.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on February 20, 2017, 12:32 AM
 */

#include "Room.h"
#include "util/Dbg.h"
#include "Game.h"

using namespace std;

Room::Room(int num, int maxp) : pi(num, maxp), shouldUpdate(true), newConnections(false), 
	newPlayers(false), ul_cq(cqProt, defer_lock), ul_pq(pqProt, defer_lock), game(num){
    //load room save file?
}

/*Room::Room(const Room& orig) {
    orig.
}*/

Room::~Room() {
}

void Room::tfunc() {
    DBG::sig("Thread of room " + to_string(pi.roomId) + " started.");
    while(true){
	//DBG::sig("Checking for new Players in " + to_string(pi.roomId) + " room");
	if(newPlayers){
	    pqProt.lock();
	    while(!pQueue.empty()){
		game.addPlayer(pQueue.back());
		DBG::sig("Player added to players in " + to_string(pi.roomId) + " room");
		pQueue.pop_back();
	    }
	    newPlayers = false;
	    pqProt.unlock();
	}
	cv_pq.notify_all();
	game.turn();
	//for(vector<Player*>::iterator it = players.begin(); it != players.end(); ++it){
	    //(*it)->
	    /*Player* haha = *it;
	    it = players.erase(it);
	    --it;
	    delete haha;*/
	//}
        this_thread::sleep_for(chrono::milliseconds(1000)); //temp boundry
    }
}

void Room::pcFunc() {
    vector<Player*> toBeAdded;
    while(true){
	ul_cq.lock();	
	cv_cq.wait(ul_cq, [&](){return newConnections.load();});
	DBG::sig("connection maker function notified in " + to_string(pi.roomId) + " room");
	while(!cQueue.empty()){
	    Connection* c = cQueue.back();
	    Player* p = new Player(c);
	    toBeAdded.push_back(p);
	    DBG::sig("Player added to tobeAdded queue in " + to_string(pi.roomId) + " room");
	    cQueue.pop_back();
	}
	newConnections = false;
	ul_cq.unlock();

	ul_pq.lock();
	cv_pq.wait(ul_pq, [&](){return !newPlayers.load();});
	while(!toBeAdded.empty()){
	    pQueue.push_back(toBeAdded.back());
	    toBeAdded.pop_back();
	    DBG::sig("Player added to pQueue queue in " + to_string(pi.roomId) + " room");
	}
	newPlayers = true;
	ul_pq.unlock();
    }
}


void Room::start() {
    roomLooper = new thread(&Room::tfunc, this);
    playerCreator = new thread(&Room::pcFunc, this);
}

void Room::updateMe(publicInfo& ref) {
    if (shouldUpdate) {
	DBG::sig("should update so updating..");
        piProt.lowLock();
        ref = pi;
	shouldUpdate = false;
        piProt.lowUnlock();
    }
}

int Room::addConnection(Connection* c){
    piProt.highLock();
    if(pi.playersCount < pi.maxPlayers){
	pi.playersCount++;
	shouldUpdate = true;
    }else{
	piProt.highUnlock();
	return 1;	
    }
    piProt.highUnlock();
    
    cqProt.lock();
    cQueue.push_back(c);
    newConnections = true;
    cqProt.unlock();
    cv_cq.notify_all(); 
}

