//
// Created by sari yono on 4/15/17.
//

#ifndef CPPSERVER_CLIENT_H
#define CPPSERVER_CLIENT_H

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
class Client {
public:
    char *clientName;
    int clientId;
    int socket;

public:
    Client();
    //name and id setters
    void SetClientName(const char *name);
    void SetClientId(int id);
};
#endif //CPPSERVER_CLIENT_H
