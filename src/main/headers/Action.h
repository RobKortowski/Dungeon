/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Action.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 2, 2017, 2:40 PM
 */

#ifndef ACTION_H
#define ACTION_H

#include <atomic>

enum moves{
    idle, up, upr, r, dwnr, dwn, dwnl, l, upl
};

enum doings{
    dnone, a, b, c, d, e, f 
};

enum additionals{
    anone, leave, force_leave
};

struct Action {
   
    /* determines whether additional request was made by client*/
    std::atomic<additionals> command;

    /*direction which character faces as angle <0,1> section*/
    std::atomic<float> angle;
    
    /*latest move of the client, idle can always be overwritten by others, others, overwrites others*/
    std::atomic<moves> move;

    /*latest left hand doing, letter coresponds fixed slot in client leftbar*/
    std::atomic<doings> primary;

    /*latest right hand doing, letter coresponds fixed slot in client leftbar*/
    std::atomic<doings> secondary;

    /*special*/
    std::atomic<bool> special;
    
    
    Action();
    void reset();

};

#endif /* ACTION_H */

