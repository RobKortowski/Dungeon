/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Air.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 28, 2017, 12:46 AM
 */

#ifndef AIR_H
#define AIR_H

#include "Block.h"


struct Air : Block {
    Air();
    std::string to_string() override;

};

#endif /* AIR_H */

