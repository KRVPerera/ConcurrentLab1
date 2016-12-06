//
// Created by root on 12/6/16.
//

#include <cstdlib>
#include "Node.h"

Node::Node () {
    value = -1;
    next = (Node *) nullptr;
    prev = (Node *) nullptr;
}

Node::~Node () {
    free(next);
    free(prev);
}

Node::Node (int val) : Node() {
    value = val;
}