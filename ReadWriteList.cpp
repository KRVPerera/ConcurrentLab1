//
// Created by damith on 12/12/16.
//

#include "ReadWriteList.h"

ReadWriteList::ReadWriteList() : SerialList() {
    pthread_rwlock_init(&glb_rwlock, NULL);
}

void ReadWriteList::Print() {
    pthread_rwlock_rdlock(&glb_rwlock);
    SerialList::Print();
    pthread_rwlock_unlock(&glb_rwlock);
}

ReadWriteList::~ReadWriteList() {
    pthread_rwlock_destroy(&glb_rwlock);
}

Node *ReadWriteList::Find(int i) {
    pthread_rwlock_rdlock(&glb_rwlock);
    Node *found = SerialList::Find(i);
    pthread_rwlock_unlock(&glb_rwlock);
    return found;
}

bool ReadWriteList::Member(int i) {
    pthread_rwlock_rdlock(&glb_rwlock);
    bool found = SerialList::Member(i);
    pthread_rwlock_unlock(&glb_rwlock);
    return found;
}

void ReadWriteList::Insert(int i) {
    pthread_rwlock_wrlock(&glb_rwlock);
    SerialList::Insert(i);
    pthread_rwlock_unlock(&glb_rwlock);
}

void ReadWriteList::Delete(int i) {
    pthread_rwlock_wrlock(&glb_rwlock);
    Node *x = SerialList::Find(i);
    if (x != nil) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
        delete (x);
    }
    pthread_rwlock_unlock(&glb_rwlock);
}