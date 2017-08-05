#include <iostream>
#include <string>
#include <thread>
#include "ConnAccepter.h"
#include "util/Settings.h"
#include "Dbg.h"
#include "RoomManager.h"

#define ROOM_INIT_COUNT 1

using namespace std;

void responder() {
    while (true) {
        string a;
        cin >> a;
        if (a.compare("close\n")) {
            cout << "terminating" << endl;
            terminate();
            return;
        }
    }
}

int main() {
    Settings::setDebug(true);
    DBG::sig("Program started.");
	
    RoomManager rm(ROOM_INIT_COUNT);
    ConnManager cm(rm);
    ConnAccepter a(cm);
    cm.join();

    //	thread console(responder);
    //	console.join();	
    return 0;
}
