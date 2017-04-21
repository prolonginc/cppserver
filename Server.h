//
// Created by sari yono on 4/12/17.
//

#ifndef CPPSERVER_SERVER_H
#define CPPSERVER_SERVER_H

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

#include <cstdio>

//socket headers
#include <sys/socket.h>
#include <netinet/in.h>
//the client class
#include "client.h"
#include "thread.h"

#define PORT 30001

using namespace std;

class Server {

private:
    //initiate a vector for Clients
    static vector<Client> chatClients;

   int serverSocket, clientSocket;

    //https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html

    struct sockaddr_in serverAddr, clientAddr;
    //buffer size
    char buffer[256];

public:
    Server();
    void receiveAndSend();
    static void * ClientHandler(void *args);

private:

    static void ListClients();
    static void PublicBroadcast(string *message);
    static int getClientIndex(Client *c);
};

#endif //CPPSERVER_SERVER_H
