//
// Created by krv on 12/10/16.
//

#ifndef CONCURRENTTHLAB_1_SERIALDRIVER_H
#define CONCURRENTTHLAB_1_SERIALDRIVER_H

#include <vector>
#include "SerialList.h"

class SerialDriver {
private:
    float member_frac = 0.50, insert_frac = 0.25, delete_frac = 0.25;
    int num_population = 1000; // n
    int num_operations = 10000; // m
public:
    void Drive();

    SerialDriver(float member_f, float insert_f, float delete_f);

    static void populate_list(SerialList *list, std::vector<int> *population, int i);
};


#endif //CONCURRENTTHLAB_1_SERIALDRIVER_H
