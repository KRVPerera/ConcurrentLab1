//
// Created by root on 12/6/16.
//

#ifndef CONCURRENTTHLAB_1_SERIALLIST_H
#define CONCURRENTTHLAB_1_SERIALLIST_H


#include "LinkedList.h"

class SerialList : public LinkedList{
protected:
    Node *Find(int i) override;

public:
    void Delete (int i) override;

    bool Member(int i) override;

    void Insert (int i) override;

    int Size() override;


};

#endif //CONCURRENTTHLAB_1_SERIALLIST_H
