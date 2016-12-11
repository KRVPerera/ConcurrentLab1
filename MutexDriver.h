//
// Created by krv on 12/11/16.
//

#ifndef CONCURRENTTHLAB_1_MUTEXDRIVER_H
#define CONCURRENTTHLAB_1_MUTEXDRIVER_H


#include <vector>
#include "MutexList.h"

class MutexDriver {
private:
    float member_frac = 0.50, insert_frac = 0.25, delete_frac = 0.25;
    int num_population = 1000; // n
    int num_operations = 10000; // m
public:
    void Drive();

    MutexDriver(float member_f, float insert_f, float delete_f);

    static void populate_list(MutexList *list, std::vector<int> *population, int i);

};


#endif //CONCURRENTTHLAB_1_MUTEXDRIVER_H
