/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "Block.h"
#include "Chunk.h"
#include "InnerCube.h"
#include "Air.h"
#include "Dirt.h"
#include <string>

using namespace std;

std::string Air::to_string() {
    std::string tmp = std::string("A");
    tmp += *this->pos;
    return tmp;
}

Air::Air() {
    shouldLog = false;
}

std::string Dirt::to_string() {
    std::string tmp = std::string("D");
    tmp += *this->pos;
    return tmp;
}

Dirt::Dirt() {
    shouldLog = true;
}


std::string Chunk::to_string() {
    std::string tmp = std::string("Y");
    tmp += x;
    tmp += "|";
    tmp += y;
    tmp += "|";
    tmp += z;
    tmp += "Y";
    return tmp;
}

std::string InnerCube::to_string() {
    std::string tmp = std::string("X");
    tmp += *this->pos;
    return tmp;
}
