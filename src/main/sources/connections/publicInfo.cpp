/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   publicInfo.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on February 20, 2017, 10:50 PM
 */

#include "connections/publicInfo.h"

publicInfo::publicInfo(int roomId) : roomId(roomId), playersCount(0), maxPlayers(10){
}

publicInfo::publicInfo(int roomId, int maxPlayers) : 
roomId(roomId), playersCount(0), maxPlayers(maxPlayers){
}

publicInfo::publicInfo(const publicInfo& orig) {
    roomId = orig.roomId;
    playersCount = orig.playersCount;
    maxPlayers = orig.maxPlayers;
}

publicInfo::~publicInfo() {
}

