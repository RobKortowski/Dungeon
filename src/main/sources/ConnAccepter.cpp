#include <iostream>
#include <thread>
#include "ConnAccepter.h"
#include "Dbg.h"
#include "Connection.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 3450
#define MAXQUEUE 15

using namespace std;

ConnAccepter::ConnAccepter(ConnManager& manager) : manager(manager) {
    if (serverInit() == -1)
        throw "Server init failed!";
    acc = new thread(&ConnAccepter::tfunc, this);
    //	acc->join();
    DBG::sig("ConnAccepter created");
}

ConnAccepter::~ConnAccepter() {
    delete acc;
}

void ConnAccepter::tfunc() {
    /*if (listen(sockfd, MAXQUEUE) == -1){
        DBG::sig("Server not listening!");
	throw "Server not listening!";
    }*/
    while (true) {
	int status = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *) &their_addr,
		(socklen_t*) & sin_size);
	if (status == -1 || status == 0){
	    DBG::sig("No valid init msg found. " + to_string(status));
            continue;
	}else if ((connect(sockfd, (struct sockaddr *) &their_addr, sin_size)) == -1) {
	    DBG::sig("Acceptation fail");
            continue;
        }else{
	    manager.addConnection(new Connection(sockfd, "test"/*inet_ntoa(their_addr.sin_addr)*/));
	    sockfd = newSocket();
	}
    }
}

int ConnAccepter::serverInit() {
    my_addr.sin_family = AF_INET; // filling up addres struct 
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(my_addr.sin_zero), '\0', sizeof my_addr.sin_zero);
    sin_size = sizeof (struct sockaddr_in);
    if((sockfd = newSocket())==-1){
	DBG::sig("Socket construction failed");
	throw "Socket construction failed";
    }
    DBG::sig("Server initialised");    
    return 1;
}

int ConnAccepter::newSocket(){
    DBG::sig("Creating socket");    
    int new_socket;
    if ((new_socket = socket(PF_INET, SOCK_DGRAM, 0)) == -1) // creating socket
        return -1;
    if (setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1)
        return -1;
    if (bind(new_socket, (struct sockaddr *) &my_addr, sizeof (struct sockaddr)) == -1) // bind soc with addr
        return -1;
    string msg = "Socket " + to_string(new_socket) + " created.";
    DBG::sig(msg);    
    return new_socket;
}
