/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.h
 * Author: Robert Kortowski robjudo@wp.pl
 *
 * Created on March 29, 2017, 6:15 PM
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "BoundingVolume.h"


struct Circle : BoundingVolume {
    
    void claim(Entity*, Map*) override;
    double getProperty(int) override;

    double r;
    double height;
    
};

#endif /* CIRCLE_H */

