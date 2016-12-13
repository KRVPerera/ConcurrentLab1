//
// Created by krv on 12/10/16.
//

#ifndef CONCURRENTTHLAB_1_SERIALDRIVER_H
#define CONCURRENTTHLAB_1_SERIALDRIVER_H

#include <vector>
#include "SerialList.h"
#include "Common.h"

class SerialDriver {
private:
    float member_frac = 0.50, insert_frac = 0.25, delete_frac = 0.25;
    int num_population = 1000; // n
    int num_operations = 10000; // m
public:
    void Drive();

    SerialDriver(float member_f, float insert_f, int pop, int ops);

    static void populate_list(LinkedList *, std::vector<Operation> *, int n_pop, int n_op, int in_f, int d_f);
};


#endif //CONCURRENTTHLAB_1_SERIALDRIVER_H
