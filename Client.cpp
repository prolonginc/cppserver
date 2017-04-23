#include "client.h"

using namespace std;

Client::Client() {
//    this->clientName = (string *) malloc(NAME_MAX_LENGTH+1);
}

void Client::setClientName(string name) {
    this->clientName = name;
}

void Client::setClientId(int id) {
    this->clientId = id;
}
