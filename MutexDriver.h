//
// Created by krv on 12/11/16.
//

#ifndef CONCURRENTTHLAB_1_MUTEXDRIVER_H
#define CONCURRENTTHLAB_1_MUTEXDRIVER_H


#include <vector>
#include "MutexList.h"

#define MAX_THREADS 4

typedef struct thread_data {
    int tid;
    float insert_f;
    float del_f;
    int tot_loc_ops;
    MutexList *list;

} thread_data;

class MutexDriver {
private:
    float member_frac = 0.50, insert_frac = 0.25, delete_frac = 0.25;
    int num_population = 1000; // n
    int num_operations = 10000; // m
    int THREAD_COUNT = 2;

//     // used to generate unique values
public:
    void Drive();

    MutexDriver(float member_f, float insert_f, float delete_f, int thread_count);

    static void populate_list(MutexList *list, std::vector<int> *population, int i);

    float ThreadCreation(MutexList *list);

    static void *work(void *tid);
};


#endif //CONCURRENTTHLAB_1_MUTEXDRIVER_H
