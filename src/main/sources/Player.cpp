/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on March 1, 2017, 12:39 AM
 */

#include "Player.h"
#include "Dbg.h"
#include "Map.h"
#include <string>

using namespace std;

Player::Player(Connection* c) {
    conn = c;
    c->setState(true); // setting ingame state 

    //init player from file
    init(); 
    
    DBG::sig("Player Created");
}

Player::Player(const Player& orig) {
}

Player::~Player() {
    delete conn;
}

void Player::calcTurn(){
    //DBG::sig("calcTurn invoked"); 
}

void Player::doTurn(){
    
}

void Player::addVisible(Block* b) {
}

void Player::clearVisible() {
    logg = "";
}

void Player::addVisible(Entity* e){
     
}

void Player::addToLog(std::string s) {
    logg += s;
}

void Player::sendLog() {
    string msg = "SERVER";
    msg+=logg;
    conn->sendMsg(msg); 
}

bool Player::obey(Entity* e) {

}

void Player::colide(Entity* e) {

}

void Player::action(Entity* e, int a){

}

double Player::getProperty(int a){
    if(a==1){
	return 50;
    }
}

bool Player::isPlayer(){
    return true;   
}

std::string Player::to_string() {
    return "Player";
}

void Player::init() {
    id = 1;
    woken = true;
    dependent = false;
    x=y=z=50;
    xx=yy=zz=50.0;
    angle = 0.0;
    sx=sy=sz=0.0;
    mass = 100.0;
}
