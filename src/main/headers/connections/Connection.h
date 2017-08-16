#ifndef CONNECTION_H
#define CONNECTION_H

#define BLEN 128

#include<string>
#include<mutex>
#include<thread>
#include <atomic>
#include "Action.h"

class Connection {
public:
    Connection(int, std::string);
    ~Connection();
   
    /*sends string through socked specified by socketfd*/
    int sendMsg(std::string);

    /*returns "" when there is no new msg from socket, string msg otherwise*/
    std::string getMsg();
   
    /*determines whether Connection is in closed state*/
    bool isClosed();

    /*sets inGame bool which determines thread behavior*/
    void setState(bool);

    
private:
    /*inGame state determines thread behavior*/
    std::atomic<bool> inGame;
    
    /*pointer to action rdy for collecting by room thread*/
    std::atomic<Action*> current;
  
    /*pointer to action to be swapped with current when current is going to be processed by room thread*/
    std::atomic<Action*> swapped;
  
    
    /*protects msg string*/
    std::mutex mutex;

    /* NOTE: change msg to atomic? */ 
    std::string msg;

    /*determines whether msg has changed since last getMsg() call*/
    std::atomic<bool> newMsg;

    
    int sockfd;
    std::string ip;
    std::thread* receiver;
    char buffer[1024*128];

    std::atomic<bool> closed; 


    void setClosed(bool);
    void tfunc();

    void interpret(std::string&);    

};

#endif
