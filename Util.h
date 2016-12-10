//
// Created by krv on 12/10/16.
//

#ifndef CONCURRENTTHLAB_1_UTIL_H
#define CONCURRENTTHLAB_1_UTIL_H

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

static class Util {
public:


    static double Mean(vector<double> times);

    static double StandardDeviation(vector<double> times);

    static long RequiredSampleSize(double sd, double mean);
};


#endif //CONCURRENTTHLAB_1_UTIL_H
