/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Block.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 20, 2017, 10:13 PM
 */

#ifndef BLOCK_H
#define BLOCK_H

#include "Loggable.h"
#include "InnerCube.h"
#include <string>

class InnerCube;

struct Block : Loggable{

    int x, y, z;
    
    bool shouldLog;
    InnerCube* parent;    
    std::string* pos;
};

#endif /* BLOCK_H */

