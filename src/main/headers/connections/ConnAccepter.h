#ifndef CONNACCEPTER_H
#define CONNACCEPTER_H

#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "connections/ConnManager.h"

class ConnAccepter {
public:
    int test = 1;
    std::thread* acc;

    ConnAccepter(ConnManager&);
    virtual ~ConnAccepter();

private:
    //server stuff
    int sockfd, new_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int sin_size;
    int yes = 1;
    char buffer[1024];

    ConnManager& manager;

    int serverInit();
    int newSocket();
    void tfunc();

};

#endif
