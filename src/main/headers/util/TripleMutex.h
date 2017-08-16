/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TripleMutex.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on February 20, 2017, 8:44 PM
 */

#ifndef TRIPLEMUTEX_H
#define TRIPLEMUTEX_H

#include <mutex>

class TripleMutex {
public:
    TripleMutex();
    TripleMutex(const TripleMutex& orig);
    virtual ~TripleMutex();

    void lowLock();
    void lowUnlock();
    void highLock();
    void highUnlock();
    
private:
    std::mutex data;
    std::mutex next;
    std::mutex lowp;
    
};

#endif /* TRIPLEMUTEX_H */

