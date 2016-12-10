//
// Created by krv on 12/10/16.
//

#include <cmath>
#include "Util.h"
#include <algorithm>

using namespace std;
// N = (100zs/rx)^2, r - accuracy (5%), s - standard deviation, x - mean, z = 1.960 (95%) - TAKE THE CEIL
/// This function gives the required number of samples to take to achieve
/// accuracy of 5% and 95% confidence
/// \param sd standard deviation
/// \param mean average
/// \return

long Util::RequiredSampleSize(float sd, float mean) {
    long N = (long) ceil(((float) 100 * 1.960 * sd) / (5 * mean));
    return N;
}

float Util::Mean(vector<float> times) {
    int size = times.size();
    long sum = accumulate(times.begin(), times.end(), 0);
    return (double) sum / size;
}

float Util::StandardDeviation(vector<float> times) {
    double mean = Util::Mean(times);
    double variance = 0;
    for (int i = 0; i < times.size(); ++i) {
        variance += pow(times[i] - mean, 2);
    }
    variance = variance / times.size();
    return sqrt(variance);
}

float Util::elapsed_time_msec(struct timespec *begin, struct timespec *end,
                              unsigned long *sec, unsigned long *nsec) {
    if (end->tv_nsec < begin->tv_nsec) {
        *nsec = 1000000000 - (begin->tv_nsec - end->tv_nsec);
        *sec = end->tv_sec - begin->tv_sec - 1;
    } else {
        *nsec = end->tv_nsec - begin->tv_nsec;
        *sec = end->tv_sec - begin->tv_sec;
    }
    return (float) (*sec) * 1000 + ((float) (*nsec)) / 1000000.0;
}
