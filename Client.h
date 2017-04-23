//
// Created by sari yono on 4/15/17.
//

#ifndef CPPSERVER_CLIENT_H
#define CPPSERVER_CLIENT_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#define NAME_MAX_LENGTH 20

using namespace std;
class Client {
public:
    string *clientName;
    int clientId;
    int socket;

public:
    Client();
    //name and id setters
    void setClientName(std::string *clientName);
    void setClientId(int id);
};
#endif //CPPSERVER_CLIENT_H
