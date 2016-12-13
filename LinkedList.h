//
// Created by root on 12/6/16.
//

#ifndef CONCURRENTTHLAB_1_LINKEDLIST_H
#define CONCURRENTTHLAB_1_LINKEDLIST_H


#include <iostream>
#include "Node.h"

class LinkedList {
protected:
    virtual Node *Find(int) = 0;
    Node * nil;
public:
    LinkedList ();
    void Print();
    ~LinkedList ();

    virtual int Delete(int) = 0;

    virtual int Insert(int) = 0;
    virtual bool Member(int) = 0;
    virtual int Size() = 0;
};


#endif //CONCURRENTTHLAB_1_LINKEDLIST_H
