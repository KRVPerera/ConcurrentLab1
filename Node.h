//
// Created by root on 12/6/16.
//

#ifndef CONCURRENTTHLAB_1_NODE_H
#define CONCURRENTTHLAB_1_NODE_H


class Node {
public:
    Node();

    Node (int val);

    virtual ~Node ();

    int value;
    Node * next;
    Node * prev;
};


#endif //CONCURRENTTHLAB_1_NODE_H
