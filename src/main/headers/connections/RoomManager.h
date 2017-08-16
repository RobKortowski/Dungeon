/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RoomManager.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on February 19, 2017, 9:37 PM
 */

#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <vector>
#include <atomic>
#include "connections/Room.h"
#include "connections/publicInfo.h"
#include "connections/Connection.h"

class RoomManager {
public:
    RoomManager(int);
    RoomManager(const RoomManager& orig);
    virtual ~RoomManager();

    bool repChanged(); 
    void getRep(std::string&);
    int addToRoom(int, Connection*);
private:
    int roomCount;
    
    std::vector<Room*> rooms;
    std::vector<publicInfo*> pInfos;

    std::mutex repProt;
    std::string infoRep;

    std::atomic<bool> changed;
    std::thread* updater;

    void pInfosUpdater();
};

#endif /* ROOMMANAGER_H */

