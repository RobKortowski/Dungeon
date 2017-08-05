/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 19, 2017, 6:06 PM
 */

#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Map.h"

class Game {
public:
    Game(int);
    virtual ~Game();

    /*Adds player to players vector*/
    void addPlayer(Player*);

    /*Invokes game turn*/
    void turn();


private:
    /*game number useful for loading map etc*/
    const int gameNum;

    /*game map*/
    Map map;


};

#endif /* GAME_H */

