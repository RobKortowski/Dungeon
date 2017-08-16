/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   publicInfo.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on February 20, 2017, 10:50 PM
 */

#ifndef PUBLICINFO_H
#define PUBLICINFO_H

struct publicInfo {
public:
    int roomId;
    int playersCount;
    int maxPlayers;
    
    publicInfo(int);
    publicInfo(int, int);
    publicInfo(const publicInfo& orig);
    virtual ~publicInfo();
private:

};

#endif /* PUBLICINFO_H */

