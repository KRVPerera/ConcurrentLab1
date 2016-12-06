//
// Created by root on 12/6/16.
//

#ifndef CONCURRENTTHLAB_1_LINKEDLIST_H
#define CONCURRENTTHLAB_1_LINKEDLIST_H


#include "Node.h"

class LinkedList {
public:
    LinkedList ();

    Node * head;
    Node * nil;
public:
    virtual void Delete(int) = 0;
    virtual Node Member(int) = 0;
    virtual void Insert(int) = 0;
};


#endif //CONCURRENTTHLAB_1_LINKEDLIST_H
