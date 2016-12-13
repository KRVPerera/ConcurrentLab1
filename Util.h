//
// Created by krv on 12/10/16.
//

#ifndef CONCURRENTTHLAB_1_UTIL_H
#define CONCURRENTTHLAB_1_UTIL_H

#include <vector>
#include <time.h>
#include "LinkedList.h"
#include "Common.h"
#include "SerialList.h"


class Util {
public:
    static float Mean(std::vector<float> times);

    static float StandardDeviation(std::vector<float> times);

    static long RequiredSampleSize(float sd, float mean);


    static float elapsed_time_nsec(timespec *begin, timespec *end, unsigned long *sec, unsigned long *nsec);

    static float elapsed_time_msec(timespec *begin, timespec *end, unsigned long *sec, unsigned long *nsec);

    static float elapsed_time_microsec(timespec *begin, timespec *end, unsigned long *sec, unsigned long *nsec);

    static void
    populate_list(SerialList *list, std::vector<Operation> *gen, int population, int num_ops, int ins_f, int del_f);
};

#endif //CONCURRENTTHLAB_1_UTIL_H
