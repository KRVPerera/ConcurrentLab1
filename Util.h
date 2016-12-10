//
// Created by krv on 12/10/16.
//

#ifndef CONCURRENTTHLAB_1_UTIL_H
#define CONCURRENTTHLAB_1_UTIL_H

#include <vector>


class Util {
public:
    static float Mean(std::vector<float> times);

    static float StandardDeviation(std::vector<float> times);

    static long RequiredSampleSize(float sd, float mean);

    static float
    elapsed_time_msec(struct timespec *begin, struct timespec *end, unsigned long *sec, unsigned long *nsec);
};

#endif //CONCURRENTTHLAB_1_UTIL_H
