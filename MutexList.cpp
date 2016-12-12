//
// Created by krv on 12/10/16.
//

#include "MutexList.h"

MutexList::MutexList() : SerialList() {
    pthread_mutex_init(&glb_mutex, NULL);
}

void MutexList::Print() {
    pthread_mutex_lock(&glb_mutex);
    SerialList::Print();
    pthread_mutex_unlock(&glb_mutex);
}

MutexList::~MutexList() {
    pthread_mutex_destroy(&glb_mutex);
}

Node *MutexList::Find(int i) {
    pthread_mutex_lock(&glb_mutex);
    Node *found = SerialList::Find(i);
    pthread_mutex_unlock(&glb_mutex);
    return found;
}

bool MutexList::Member(int i) {
    pthread_mutex_lock(&glb_mutex);
    bool found = SerialList::Member(i);
    pthread_mutex_unlock(&glb_mutex);
    return found;
}

void MutexList::Insert(int i) {
    pthread_mutex_lock(&glb_mutex);
    SerialList::Insert(i);
    pthread_mutex_unlock(&glb_mutex);
}

void MutexList::Delete(int i) {
    pthread_mutex_lock(&glb_mutex);
    Node *x = SerialList::Find(i);
    if (x != nil) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
        delete (x);
    }
    pthread_mutex_unlock(&glb_mutex);
}