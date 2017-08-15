/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dbg.cpp
 * Author: Robert Kortowski robjudo@wp.pl
 * 
 * Created on February 16, 2017, 1:08 AM
 */

#include "util/Dbg.h"
#include <iostream>
#include "util/Settings.h"

using namespace std;

namespace DBG {
    void sig(string msg) {
		if(Settings::shouldDebug()){
       		cout << msg << endl;
		}
    }
}

