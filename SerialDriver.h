//
// Created by krv on 12/10/16.
//

#ifndef CONCURRENTTHLAB_1_SERIALDRIVER_H
#define CONCURRENTTHLAB_1_SERIALDRIVER_H


#include "SerialList.h"

class SerialDriver {
public:
    void Drive();

    static void populate_list(SerialList *list, int population);
};


#endif //CONCURRENTTHLAB_1_SERIALDRIVER_H
