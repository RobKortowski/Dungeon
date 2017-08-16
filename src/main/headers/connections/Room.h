/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Room.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on February 20, 2017, 12:32 AM
 */

#ifndef ROOM_H
#define ROOM_H

#include <thread>
#include <atomic>
#include <vector>
#include <condition_variable>

#include "connections/publicInfo.h"
#include "util/TripleMutex.h"
#include "connections/Connection.h"
#include "Player.h"
#include "Game.h"

class Room {
public:
    Room(int,int maxp = 5);
    //Room(const Room& orig);
    virtual ~Room();
    
    void start();
    void updateMe(publicInfo&);

    /*adds connection to c-n queue, to be transformed to player class
     0- successful 
     1- room is full
     2- failed in other way*/
    int addConnection(Connection*);

private:
    /*flag, determines whether public info changed since last updateMe call.*/
    std::atomic<bool> shouldUpdate; 
    
    /*flag, determines whether another connections was added*/
    std::atomic<bool> newConnections;

    /*flag, determines whether another Player was added*/
    std::atomic<bool> newPlayers;
    
    publicInfo pi;
    
    /*protects pi variable*/
    TripleMutex piProt;
    
    /*room's main thread*/ 
    std::thread* roomLooper;
    void tfunc();
    
    /*room's player constructing thread*/
    std::thread* playerCreator;
    void pcFunc();
   
    
    /*connections waiting to e transformed to Player class by playerCreator thread*/
    std::vector<Connection*> cQueue;

    /*protects cQueue*/
    std::mutex cqProt;

    /*unique lock for connection queue*/
    std::unique_lock<std::mutex> ul_cq;
    
    /*condition variable for connection queue*/
    std::condition_variable cv_cq;

    
    /*players waiting to be added to players vector by main game thread (roomLooper)*/
    std::vector<Player*> pQueue;
  
    /*protects pQueue*/
    std::mutex pqProt;
    
    /*unique lock for players queue*/
    std::unique_lock<std::mutex> ul_pq;
    
    /*condition variable for players queue*/
    std::condition_variable cv_pq;


    /*################################ GAME STUFF ################################*/
    /*main players list*/
    Game game;
    
    
};

#endif /* ROOM_H */

