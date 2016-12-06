//
// Created by root on 12/6/16.
//

#include "LinkedList.h"

LinkedList::LinkedList(){
    nil = new Node;
    nil->next = nil->prev;
    nil->prev = nil->next;
}