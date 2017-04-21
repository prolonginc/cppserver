//
// Created by sari yono on 4/12/17.
//

#include "server.h"

using namespace std;

//Actually allocate clients
vector<Client> Server::chatClients;

Server::Server() {

    //Initialize the  mutex
    Thread::initMut();

    int yes = 1;

    //https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/tcpserver.c
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);


    //Avoid bind error if the socket was not close()'d last time;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    if(::bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(sockaddr_in)) < 0)
        cerr << "Failed during the binding process";

        listen(serverSocket, 5);

}

void Server::receiveAndSend() {

    Client *client;
    Thread *thread;

    socklen_t cliSize = sizeof(sockaddr_in);


    //run forever
    while(true) {

        client = new Client();
        thread = new Thread();

        client->socket = accept(serverSocket, (struct sockaddr *) &clientAddr, &cliSize);

        if(client->socket < 0) {
            cerr << "Error while accepting";
        }
        else {
            thread->generate((void *) Server::ClientHandler, client);
        }
    }
}

void *Server::ClientHandler(void *args) {

    //Pointer to accept()'ed Client
    Client *client = (Client *) args;
    string buffer[256-25];
    string message[256];
    int index;
    int n;

    //Add client in Static clients <vector> (Critical section!)
    Thread::lockMut((const char *) client->clientName);

    //Before adding the new client, calculate its id. (Now we have the lock)
    client->setClientId(Server::chatClients.size());
//    sprintf(buffer, "Client n.%d", client->clientId);
    client->setClientName(buffer);
    cout << "Adding client with id: " << client->clientId << endl;
    Server::chatClients.push_back(*client);

    Thread::unlockMut((const char *) client->clientName);

    while(1) {
        memset(buffer, 0, sizeof buffer);
        n = recv(client->socket, buffer, sizeof buffer, 0);

        //Client disconnected?
        if(n == 0) {
            cout << "Client " << client->clientName << " diconnected" << endl;
            close(client->socket);

            //Remove client in Static clients <vector> (Critical section!)
            Thread::lockMut((const char *) client->clientName);

            index = Server::getClientIndex(client);
            cout << "earse user with index:  " << index << "andid is: "
                 << Server::chatClients[index].clientId << endl;
            Server::chatClients.erase(Server::chatClients.begin() + index);

            Thread::unlockMut((const char *) client->clientName);

            break;
        }
        else if(n < 0) {
            cerr << "receive error: " << client->clientName << endl;
        }
        else {
            //Message is here now broadcast.
            cout << message << " " << client->clientName  << "  "  << buffer;
            cout << "Will send to all: " << message << endl;
            Server::PublicBroadcast(message);
        }
    }

    //End thread
    return NULL;
}

void Server::PublicBroadcast(string *message) {
    int size;

    //Acquire the lock
    Thread::lockMut("'PublicBroadcast()'");

    for(size_t i=0; i<chatClients.size(); i++) {

//       ssize_t	send(int, const void *, size_t, int) __DARWIN_ALIAS_C(send);
        cout << message << endl ;
        size = send(Server::chatClients[i].socket, message, message->length(),0);
        cout << size << " sent bytes." << endl;
    }

    //Release the lock
    Thread::unlockMut("'PublicBroadcast()'");
}

void Server::ListClients() {
    for(size_t i=0; i<chatClients.size(); i++) {
        cout << chatClients.at(i).clientName << endl;
    }
}

/*
  Should be called when vector<Client> clients is locked!
*/
int Server::getClientIndex(Client *client) {
    for(size_t i=0; i<chatClients.size(); i++) {
        if((Server::chatClients[i].clientId) == client->clientId) return (int) i;
    }
    cerr << "clientId not found." << endl;
    return -1;
}