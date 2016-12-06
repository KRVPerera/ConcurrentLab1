//
// Created by root on 12/6/16.
//

#include <cstdlib>
#include "Node.h"

Node::Node () {
    value = NULL;
    next = nullptr;
}

Node::Node (int val, Node * nxt) {
    value = val;
    next = nxt;
}