/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 1, 2017, 12:39 AM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "connections/Connection.h"
#include "Entity.h"
#include <string>


class Player : public Entity {
public:
    Player(Connection*);
    Player(const Player& orig);
    virtual ~Player();

    /*computes intent and next move whether its ai decision or action from conection*/
    void calcTurn() override;

    /*executes calculated in calcTurn action*/
    void doTurn() override;

    /*add to visible for entity*/
    void addVisible(Block*) override;
    void addVisible(Entity*) override;
    void clearVisible() override;
    void sendLog();
    void addToLog(std::string);

    /*calculates obediance decision for dependant moving entities*/
    bool obey(Entity*) override;

    /*phisics prawo zachowania pedu itd*/
    void colide(Entity*) override;

    /*universal actions to be implemented by various entites*/ //dmg due to wall hit, craft 1, add to eq
    void action(Entity*, int) override;

    /*to be changed to bool, more teturning types?*/
    double getProperty(int) override;
   
    /*bool determines whether msgs to log should be pushed*/
    bool isPlayer() override;

    std::string to_string() override;
    
    Connection* conn;
    
    /*msgs to be send to players console*/
    std::string logg;

    /*visible vactors*/
    std::vector<Block*> visibleBlocks;
    std::vector<Entity*> visibleEntity;
    
    /*temporary init*/
    void init();
    

};

#endif /* PLAYER_H */

