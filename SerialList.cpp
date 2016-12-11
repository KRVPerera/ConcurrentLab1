//
// Created by root on 12/6/16.
//

#include "SerialList.h"

SerialList::SerialList() : LinkedList() {}


void SerialList::Delete(int i) {
    Node *x = Find(i);
    if (x != nil) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
        delete (x);
    }
}

Node *SerialList::Find(int i) {
    Node *x = nil->next;
    while (x != nil && x->value != i) {
        x = x->next;
    }
    if (x != nil && x->value)
        return x;
}

bool SerialList::Member(int i) {
    Node *x = nil->next;
    while (x != nil && x->value != i) {
        x = x->next;
    }
    if (x != nil && x->value == i) {
        return true;
    } else {
        return false;
    }
}

void SerialList::Insert(int i) {
    Node *x = new Node(i);
    x->next = nil->next;
    nil->next->prev = x;
    nil->next = x;
    x->prev = nil;
}

int SerialList::Size() {
    int count = 0;
    Node *x = nil->next;
    while (x != nil) {
        x = x->next;
        count++;
    }
    return count;
}



