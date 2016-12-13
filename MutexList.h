//
// Created by krv on 12/10/16.
//

#ifndef CONCURRENTTHLAB_1_MUTEXLIST_H
#define CONCURRENTTHLAB_1_MUTEXLIST_H


#include "SerialList.h"
#include <pthread.h>

class MutexList : public SerialList {

private:
    pthread_mutex_t glb_mutex;

protected:
    Node *Find(int i) override;

public:
    MutexList();

    void Print();

    int Delete(int i) override;

    bool Member(int i) override;

    int Insert(int i) override;

    ~MutexList() ;
};


#endif //CONCURRENTTHLAB_1_MUTEXLIST_H
