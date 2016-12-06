//
// Created by root on 12/6/16.
//

#include "SerialList.h"

void SerialList::Delete (int i) {
    Node * x = Member(i);
    x->prev->next = x->next;
    x->next->prev = x->prev;
    delete (x);
}

Node * SerialList::Member (int i) {
    Node * x = nil->next;
    while(x != nil && x->value != i){
        x = x->next;
    }
    return x;
}

void SerialList::Insert (int i) {
    Node * x = new Node(i);
    x->next = nil->next;
    nil->next->prev = x;
    nil->next = x;
    x->prev = nil;
}
