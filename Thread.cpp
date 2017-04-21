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
        //todo clean up by removing those after debugging complete

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
        //todo clean up by removing those after debugging complete

        cout << "mutex initted." << endl;
        return 0;
    }
}

int Thread::lockMut(const char *identifier) {
    if(pthread_mutex_lock(&Thread::mut) == 0) {
        return 0;
    }
    else {
        cerr << "Error during " << identifier << " was locking" << endl;
        return -1;
    }
}

int Thread::unlockMut(const char *identifier) {
    cout << identifier << " trying to lock" << endl;
    if(pthread_mutex_unlock(&Thread::mut) == 0) {
        //todo clean up by removing those after debugging complete
        cout << identifier << " released lock" << endl;
        return 0;
    }
    else {
        cerr << "Error while " << identifier << " was trying to release the lock" << endl;
        return -1;
    }
}
