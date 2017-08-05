/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Entity.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on March 24, 2017, 10:03 PM
 */

#include "Entity.h"
#include "Map.h"

Entity::Entity() {
}

Entity::Entity(const Entity& orig) {
}

Entity::~Entity() {
}

void Entity::setMap(Map* m) {
    map = m;
}


