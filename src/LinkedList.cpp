//
// Created by root on 12/6/16.
//

#include "../include/LinkedList.h"

LinkedList::LinkedList(){
    nil = new Node;
    nil->next = nil;
    nil->prev = nil;
}

LinkedList::~LinkedList () {
    Node * x = nil->next;
    Node * y = nil;
    while(x != nil){
        y = x;
        x = x->next;
        delete (y);
    }
    delete (nil);
}

void LinkedList::Print(){
    Node * x = nil->next;
    while(x != nil){
        std::cout << x->value << " ";
        x = x->next;
    }
    std::cout << std::endl;
}