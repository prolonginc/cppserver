#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{

    int client;
    int portNum = 30001; //server port
    bool is_exit = false;// initialize is_exit to false
    int bufsize = 256; //buffer size
    char buffer[bufsize];
    char* ip = "127.0.0.1";

    struct sockaddr_in server_addr;
    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0)
    {
        cout << "\nerror with socket" << endl;
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
    do {
        do {
            cin >> buffer;
            //send to socket
            send(client, buffer, bufsize, 0);

            if (*buffer == '#') {
                send(client, buffer, bufsize, 0);
                *buffer = '*';
                is_exit = true;
            }
        } while (*buffer != 42);

        do {
            recv(client, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == '#') {
                *buffer = '*';
                is_exit = true;
            }

        } while (*buffer != 42);
        cout << endl;
    } while (!is_exit);
    cout << "\ngoodbye\n";

    close(client);
    return 0;
}