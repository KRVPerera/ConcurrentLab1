//
// Created by damith on 12/12/16.
//

#ifndef CONCURRENTTHLAB_1_READWRITELIST_H
#define CONCURRENTTHLAB_1_READWRITELIST_H

#include "SerialList.h"
#include <pthread.h>

class ReadWriteList : public SerialList{

private:
    pthread_rwlock_t glb_rwlock;

protected:
    Node *Find(int i) override;

public:
    ReadWriteList();

    void Print();

    int Delete(int i) override;

    bool Member(int i) override;

    int Insert(int i) override;

    ~ReadWriteList() ;
};

#endif //CONCURRENTTHLAB_1_READWRITELIST_H
