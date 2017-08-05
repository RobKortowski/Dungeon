/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Entity.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 24, 2017, 10:03 PM
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

#include "Chunk.h"
#include "InnerCube.h"
#include "Block.h"
#include "Loggable.h"

class Map;

class Entity : Loggable{
public:
    Entity();
    Entity(const Entity& orig);
    virtual ~Entity();
    
    /*sets map variable*/
    void setMap(Map*);
   
    /*computes intent and next move whether its ai decision or action from conection*/
    virtual void calcTurn() = 0;

    /*executes calculated in calcTurn action*/
    virtual void doTurn() = 0;

    /*tmp*/
    virtual void clearVisible() = 0;
    
    /*addVisibletoEntity*/
    virtual void addVisible(Block*) = 0;
    virtual void addVisible(Entity*) = 0;

    /*calculates obediance decision for dependant moving entities*/
    virtual bool obey(Entity*) = 0;

    /*phisics prawo zachowania pedu itd*/
    virtual void colide(Entity*) = 0;

    /*universal actions to be implemented by various entites*/ //dmg due to wall hit, craft 1, add to eq
    virtual void action(Entity*, int) = 0;

    /*to be changed to bool, more teturning types?*/
    virtual double getProperty(int) = 0;
   
    /*bool determines whether msgs to log should be pushed*/
    virtual bool isPlayer() = 0;
    
    int id;

    /*determines whether entity should take turns*/
    bool woken;
    
    /*whether turn shall be taken after boss entity takes turn*/
    bool dependent;
    
    /*depending Entities*/
    std::vector<Entity*> dependants;

    /*occupies:*/
    std::vector<Chunk*> chunks;
    std::vector<InnerCube*> innerCubes;
    std::vector<Block*> blocks;
    
    /*boundind volumes*/
    //BoundingVolume major;
    
    /*chunk xyz*/
    int x, y, z;
    
    /*position on chunk*/
    double xx, yy, zz;
	    
    /* facing angle*/
    double angle;
    
    /*speed vector*/
    double sx, sy, sz;
    
    /*mass*/
    double mass;
    
    Map* map;

};

#endif /* ENTITY_H */

