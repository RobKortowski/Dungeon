/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Action.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on March 2, 2017, 2:40 PM
 */

#include "Action.h"

Action::Action(): command(anone), angle(0.0),
	move(idle), primary(dnone), secondary(dnone), special(false){
}

void Action::reset(){
    command = anone;
    move = idle;
    primary = dnone;
    secondary = dnone;
    special = false;
}
