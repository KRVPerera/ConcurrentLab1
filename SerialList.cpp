//
// Created by root on 12/6/16.
//

#include "SerialList.h"

SerialList::SerialList() : LinkedList() {}


int SerialList::Delete(int i) {
    Node *curr_p = nil->next;

    while (curr_p != nil && curr_p->value < i) {
        curr_p = curr_p->next;
    }

    if (curr_p != nil && curr_p->value == i) {
        curr_p->prev->next = curr_p->next;
        curr_p->next->prev = curr_p->prev;
        delete (curr_p);
        return 1;
    } else {
        return 0;
    }

}

Node *SerialList::Find(int i) {
    Node *x = nil->next;
    while (x != nil && x->value < i) {
        x = x->next;
    }
    if (x != nil && x->value)
        return x;
}

bool SerialList::Member(int i) {
    Node *x = nil->next;
    while (x != nil && x->value < i) {
        x = x->next;
    }
    if (x == nil || x->value > i) {
        return false;
    } else {
        return true;
    }
}

int SerialList::Insert(int i) {
    Node *curr_p = nil->next;
    while (curr_p != nil && curr_p->value < i) {
        curr_p = curr_p->next;
    }
    Node *x = new Node(i);
    if (curr_p == nil || curr_p->value > i) {
        x->next = curr_p;
        x->prev = curr_p->prev;
        curr_p->prev->next = x;
        curr_p->prev = x;
        return 1;
    } else {
        return 0;
    }
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



