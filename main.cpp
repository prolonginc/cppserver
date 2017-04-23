#include <iostream>
#include "thread.h"
#include "server.h"

int main() {
    std::cout << "Running the server!" << std::endl;
    Server *s;
    s = new Server();

    //Main loop
    s->receiveAndSend();

    return 0;
}