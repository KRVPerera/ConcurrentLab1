//
// Created by damith on 12/12/16.
//

#ifndef CONCURRENTTHLAB_1_READWRITEDRIVER_H
#define CONCURRENTTHLAB_1_READWRITEDRIVER_H

#include <vector>
#include "ReadWriteList.h"

typedef struct thread_data_rw {
    int tid;
    float insert_f;
    float del_f;
    int tot_loc_ops;
    ReadWriteList *list;

} thread_data_rw;

class ReadWriteDriver {
private:
    float member_frac = 0.50, insert_frac = 0.25, delete_frac = 0.25;
    int num_population = 1000; // n
    int num_operations = 10000; // m
    int THREAD_COUNT = 2;
public:
    void Drive();

    ReadWriteDriver(float member_f, float insert_f, float delete_f, int);

    static void populate_list(ReadWriteList *list, std::vector<int> *population, int i);

    static void *work(void *data_p);

    float ThreadCreation(ReadWriteList *list);
};

#endif //CONCURRENTTHLAB_1_READWRITEDRIVER_H
