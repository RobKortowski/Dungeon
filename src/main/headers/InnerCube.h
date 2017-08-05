/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InnerCube.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 20, 2017, 10:12 PM
 */

#ifndef INNERCUBE_H
#define INNERCUBE_H

#include "InnerCubeSeed.h"
#include "Block.h"
#include "Chunk.h"
#include <string>

class Chunk;
class Block;

typedef std::vector<Block*> b1d;
typedef std::vector<b1d> b2d;
typedef std::vector<b2d> b3d;

enum class InnerCubeType {
    air, underground, midground
};

struct InnerCube : Loggable{

    int x, y, z;
    
    /*determines whether the chunk consists only of air and empty space*/
    InnerCubeType type;

    /*determines whether chunk has already generated and stored in files unnercubes*/
    bool generated;

    /*should be nullptr (not loaded from file if already generated)*/
    InnerCubeSeed* ics;

    /*blocks*/
    b3d* blocks;

    /*visible blocks*/
    b1d* visible;

    std::string* pos;

    Chunk* parent;

    std::string to_string() override;

};

#endif /* INNERCUBE_H */

