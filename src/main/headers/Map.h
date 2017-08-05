/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 19, 2017, 7:43 PM
 */

#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Chunk.h"
#include "InnerCube.h"
#include "Player.h"
#include <string>

class Entity;

/*innerCubeSize*/
const int ICS = 10;

typedef std::vector<Chunk*> v1d;
typedef std::vector<v1d> v2d;
typedef std::vector<v2d> v3d;

enum class Mode {
    Flat, Empty
};

class Map {
public:
    /*#################### Boring ####################*/
    Map(int);
    virtual ~Map();


    /*#################### VARS ####################*/
    /*bounds of map*/
    int x, y, z;

    /*game number useful for loading map etc*/
    const int gameNum;

    /*biggest map structure*/
    v3d* chunks;

    /*woken entities which can make turns*/
    std::vector<Entity*> woken;

    /*players list, to be processed by game loop when sending data after computing all moves*/
    std::vector<Player*> players;

    /*Lookup table for string for blocks*/
    std::string*** Lookup;


    /*#################### interesting ####################*/
    /*add visible to entity*/
    void addVisible(Entity*);

    /*make player appear on the map*/
    void ascend(Player*);

    /*put entity to woken vector*/
    void wakeEntity(Entity*);

    /*remove entity from the woken vector*/
    void sleepEntity(Entity*);



    /*#################### Main methods ####################*/
    /*turn them all*/
    void calcTurns(double time);

    /*do them*/
    void doTurns();

    /*calculate visible for all entities, add to players log*/
    void calculateVisible();

    /*send that to players boy*/
    void sendLogs();

    /*Adds player to players vector*/
    void addPlayer(Player*);



    /*#################### Generator functions ####################*/
    /*generates map of given size and mode*/
    void generate(int, int, int, Mode);

    /*allocates memory to ***chunks*/
    void allocateMap(int, int, int);

    /*generates chunk by its chunk seed and type*/
    void fillChunk(Chunk*&);

    /*generates cube by its seed and type*/
    void fillInnerCube(InnerCube*&);

    /*gen Strings for blocks*/
    void generateBlockConstInfo();

    /*comparator function for intersection etc*/
    static bool compareBlocks(const Block*, const Block*);
};

#endif /* MAP_H */

