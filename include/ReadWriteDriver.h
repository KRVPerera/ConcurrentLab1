//
// Created by damith on 12/12/16.
//

#ifndef CONCURRENTTHLAB_1_READWRITEDRIVER_H
#define CONCURRENTTHLAB_1_READWRITEDRIVER_H

#include <vector>
#include "ReadWriteList.h"
#include "Common.h"

#define MAX_THREADS 4

typedef struct thread_data_rw {
    int tid;
    int num_threads;
    ReadWriteList *list;
    std::vector<Operation> *gen_list;
} thread_data_rw;

class ReadWriteDriver {
private:
    float member_frac = 0.50, insert_frac = 0.25, delete_frac = 0.25;
    int num_population = 1000; // n
    int num_operations = 10000; // m
    int thread_count = 2;
public:
    void Drive();

    ReadWriteDriver(float member_f, float insert_f, float delete_f, int thread_count);

    static void populate_list(ReadWriteList *list, std::vector<int> *population, int i);

    float ThreadCreation(ReadWriteList *list);

    static void *work(void *tid);
};

#endif //CONCURRENTTHLAB_1_READWRITEDRIVER_H
