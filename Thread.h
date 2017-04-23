//
// Created by sari yono on 4/15/17.
//

#ifndef CPPSERVER_THREAD_H
#define CPPSERVER_THREAD_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <cstdlib>

using namespace std;

class Thread {
public:
    //http://stackoverflow.com/questions/1759794/how-to-print-pthread-t
    pthread_t threadId;

private:
    static pthread_mutex_t mut;

public:
    Thread();
    int generate(void *Callback, void *args);
    int connect();

    static int initMut();
    static int lockMut(const string identifier);
    static int unlockMut(const string identifier);
};


#endif //CPPSERVER_THREAD_H
