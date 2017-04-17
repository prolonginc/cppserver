//
// Created by sari yono on 4/16/17.
//

#include "Thread.h"

using namespace std;
pthread_mutex_t Thread::mut;

Thread::Thread() {
}

//generate the thread
int Thread::generate(void *Callback, void *args) {
    int thread = 0;

    thread = pthread_create(&this->threadId, NULL, (void *(*)(void *))Callback, args);

    if(thread) {
        cerr << "cannot create thread" << endl;
        return thread;
    }
    else {
        cout << "thread is good to go." << endl;
        return 0;
    }
}

int Thread::connect() {
    pthread_join(this->threadId, NULL);
    return 0;
}

int Thread::initMut() {

    if(pthread_mutex_init(&Thread::mut, NULL) < 0) {
        cerr << "error cannot init mutex" << endl;
        return -1;
    }
    else {
        cout << "mutex initted." << endl;
        return 0;
    }
}

//todo implement mutex locking and unlocking