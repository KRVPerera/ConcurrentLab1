//
// Created by root on 12/6/16.
//

#include "../include/SerialList.h"

SerialList::SerialList() : LinkedList() {}

/// First find the pointer for the element to be deleted
/// then set pointers to skip the node to be deleted and delete it from memory
/// \param i int value to be deleted from the list
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

/// Check whether a given value is a member of the list
/// iterate from start to the end, and stop if the value is found, if the value is found return true else if it reached
/// end of the list (sentinel nil node) return false
/// \param i value to be checked
/// \return return true or false based on the value is found (member) or not
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

/// Create a new node and insert it to the start of the list
/// \param i value to be inserted to the list
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

SerialList::~SerialList() {

}

