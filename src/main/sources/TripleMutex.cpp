/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TripleMutex.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on February 20, 2017, 8:44 PM
 */

#include "TripleMutex.h"

TripleMutex::TripleMutex() {
}

TripleMutex::TripleMutex(const TripleMutex& orig) {
}

TripleMutex::~TripleMutex() {
}

void TripleMutex::lowLock(){
    lowp.lock();
    next.lock();
    data.lock();
    next.unlock();
}

void TripleMutex::lowUnlock(){
    data.unlock();
    lowp.unlock();
}

void TripleMutex::highLock(){
    next.lock();
    data.lock();
    next.unlock();
}

void TripleMutex::highUnlock(){
    data.unlock();    
}