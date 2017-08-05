/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dirt.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 28, 2017, 12:45 AM
 */

#ifndef DIRT_H
#define DIRT_H

#include "Block.h"


struct Dirt : Block {
    Dirt(); 
    std::string to_string() override;

};

#endif /* DIRT_H */

