/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Loggable.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 29, 2017, 9:33 PM
 */

#ifndef LOGGABLE_H
#define LOGGABLE_H

#include <string>

class Loggable{
public: 
    virtual std::string to_string() = 0;
};

#endif /* LOGGABLE_H */

