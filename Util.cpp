//
// Created by krv on 12/10/16.
//

#include "Util.h"

// N = (100zs/rx)^2, r - accuracy (5%), s - standard deviation, x - mean, z = 1.960 (95%) - TAKE THE CEIL
/// This function gives the required number of samples to take to achieve
/// accuracy of 5% and 95% confidence
/// \param sd
/// \param mean
/// \return
static long Util::RequiredSampleSize(double sd, double mean) {
    long N = (long) ceil(((double) 100 * 1.960 * sd) / (5 * mean));
    return N;
}

static double Util::Mean(vector<double> times) {
    int size = times.size();
    long sum = accumulate(times.begin(), times.end(), 0);
    return (double) sum / size;
}

static double Util::StandardDeviation(vector<double> times) {
    double mean = Util::Mean(times);
    double variance = 0;
    for (int i = 0; i < times.size(); ++i) {
        variance += pow(times[i] - mean, 2);
    }
    variance = variance / times.size();
    return sqrt(variance);
}