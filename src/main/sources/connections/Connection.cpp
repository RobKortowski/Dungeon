#include "connections/Connection.h"
#include "util/Dbg.h"
#include "connections/ConnAccepter.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

Connection::Connection(int sockfd, string ip) : inGame(false) {
    this->sockfd = sockfd;
    this->ip = ip;
    closed = false;
    receiver = new thread(&Connection::tfunc, this);
    current = new Action();
    swapped = new Action();
}

Connection::~Connection() {
    setClosed(true);
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
    receiver->join();
    delete receiver;
    delete current.load();
    delete swapped.load();
    //DBG::sig("DELETED CONNECTION");
}

int Connection::sendMsg(string msg) {
    int len, left, total, n;
    len = msg.length();
    const char* buf = msg.c_str();
    left = len;
    total = 0;

    while (total < len) {
        n = send(sockfd, buf + total, left, 0);
        if (n == -1) return -1;
        total += n;
        left -= n;
    }

    return 0;
}

string Connection::getMsg() {
    string result;
    if (!newMsg) {
        return "";
    } else {
	mutex.lock();
        result = msg;
        newMsg = false;
        mutex.unlock();
    }
    return result;
}

bool Connection::isClosed() {
    return closed;
}

void Connection::setClosed(bool status) {
    closed = status;
}

void Connection::tfunc() {
    int len;
    while (!isClosed()) {
        len = recv(sockfd, buffer, 1024, 0);
        if (len == 0) { //shutdown of the socket
            if(isClosed()){
		break;
	    }else{
		//TODO warn connection for bad protocol
		continue;
	    }
        } else if (len == -1) {
            continue;
        }
        buffer[len] = '\0';
        string received(buffer);
        //DBG::sig(received);
        //#################### protocol handling ####################
        if (inGame) {
	    interpret(received);
        } else {
            mutex.lock();
            msg = received;
            newMsg = true;
            mutex.unlock();
        }
    }
}

void Connection::setState(bool s) {
    inGame = s;
}

void Connection::interpret(std::string& received) {
    if (received[0] == 'N') {
        try {
            current.load()->angle = stof(received.substr(1, 4));
            moves tmp = (moves) (received[5] - '0');
            if (tmp != idle) {
                current.load()->move = tmp;
            }
            doings tmp2 = (doings) (received[6] - '0');
            if (tmp2 != dnone) {
                current.load()->primary = tmp2;
            }
            tmp2 = (doings) (received[7] - '0');
            if (tmp2 != dnone) {
                current.load()->secondary = tmp2;
            }
            if (received[8] == '1') {
                current.load()->special = true;
            }
        } catch (exception e) {
            //TODO warn connection for protocol error
        }
    } else { //if msg[0] == 'O'
        //TODO assign and interpret additional command here then set some variable to what 
        if (received == "O status") {
            sendMsg("handled by ingame state");
        } else if (received == "O leave") {
            current.load()->command = leave;
        } else if (received == "O force leave") {
            current.load()->command = force_leave;
        } else {
            //TODO warn connection for protocol error
        }
    }
}







