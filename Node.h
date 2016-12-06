//
// Created by root on 12/6/16.
//

#ifndef CONCURRENTTHLAB_1_NODE_H
#define CONCURRENTTHLAB_1_NODE_H


class Node {
public:
    Node();

    Node (int val, Node *nxt);

    int value;
    Node * next;
};


#endif //CONCURRENTTHLAB_1_NODE_H
