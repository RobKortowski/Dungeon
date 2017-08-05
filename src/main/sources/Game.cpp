/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on March 19, 2017, 6:06 PM
 */

#include <vector>

#include "Game.h"
#include "Dbg.h"

using namespace std;

Game::Game(int gameNum): gameNum(gameNum), map(gameNum){
    //TODO check if map already exists in game num folder
    //else generate map
    
}

Game::~Game() {
}

void Game::addPlayer(Player* p){
    map.addPlayer(p);
}

void Game::turn(){
    DBG::sig("turn start"); 
    map.calcTurns(0.0);
    map.doTurns();
    map.calculateVisible();
    map.sendLogs();
}

