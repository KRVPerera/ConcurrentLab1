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

int ReadWriteList::Insert(int i) {
    pthread_rwlock_wrlock(&glb_rwlock);
    int result = SerialList::Insert(i);
    pthread_rwlock_unlock(&glb_rwlock);
    return result;
}

int ReadWriteList::Delete(int i) {
    pthread_rwlock_wrlock(&glb_rwlock);
    int result = SerialList::Delete(i);
    pthread_rwlock_unlock(&glb_rwlock);
    return result;
}