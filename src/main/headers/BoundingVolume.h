/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoundingVolume.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 29, 2017, 3:29 PM
 */

#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include "Entity.h"
#include "Map.h"


enum class BoundingVolumeType{
    circle, square, rectangle
};

struct BoundingVolume {
    /*used in collision function*/
    BoundingVolumeType type;
    
    /*offset from main entity*/
    double x, y, z;
    
    /*self angle*/
    double angle;

    /*absolute xyz changed when move*/
    double absX, absY, absZ;

    /*absolute angle*/
    double absAngle;

    virtual double getProperty(int) = 0;

    virtual void claim(Entity*, Map*) = 0;


};

#endif /* BOUNDINGVOLUME_H */

