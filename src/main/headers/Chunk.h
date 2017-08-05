/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Chunk.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 20, 2017, 10:05 PM
 */

#ifndef CHUNK_H
#define CHUNK_H

#include "ChunkSeed.h"
#include "InnerCube.h"
#include <vector>
#include <string>

class InnerCube;

typedef std::vector<InnerCube*> i1d;
typedef std::vector<i1d> i2d;
typedef std::vector<i2d> i3d;

enum class ChunkType{
    air, underground, midground
};

struct Chunk : Loggable{

    int x, y, z;

    /*determines whether the chunk consists only of air and empty space*/
    ChunkType type;
    
    /*determines whether chunk has already generated and stored in files unnercubes*/
    bool generated;
   
    /*determines whether cubes is not null*/
    bool loaded; 
   
    /*should be nullptr (not loaded from file if already generated)*/
    ChunkSeed* ics;

    /*Inner cubes*/
    i3d* cubes;

    std::string to_string() override;
 
    
};

#endif /* CHUNK_H */

