//
// Created by krv on 12/10/16.
//

#ifndef CONCURRENTTHLAB_1_UTIL_H
#define CONCURRENTTHLAB_1_UTIL_H

#include <vector>
#include <time.h>
#include "Common.h"
#include "SerialList.h"


class Util {
public:
    static float Mean(std::vector<float> times);

    static float StandardDeviation(std::vector<float> times);

    /// Calculate the required sample size to achieve 5% accuracy and 95% confidence when given standard deviation
    /// and mean of the current data points. If the output is less than or equal to the sample size you already collected
    /// your sample can be considered good
    /// \param sd float type standard deviation
    /// \param mean float type mean
    /// \return long type number of samples required to run to get desired conditions
    static long RequiredSampleSize(float sd, float mean);

    static float elapsed_time_nsec(timespec *begin, timespec *end, unsigned long *sec, unsigned long *nsec);

    /// This will get two timespec pointers and get the difference between them, answer will be saved in the pointers
    /// given to it as sec and nsec and also returns the answer
    /// \param begin timepec type begin time
    /// \param end timepec type end time
    /// \param sec unsigned long type pointer to save seconds passed between begin and end
    /// \param nsec unsigned long type pointer to save nanoseconds passed between begin and end
    /// \return float value with answer in miliseconds
    static float elapsed_time_msec(timespec *begin, timespec *end, unsigned long *sec, unsigned long *nsec);

    static float elapsed_time_microsec(timespec *begin, timespec *end, unsigned long *sec, unsigned long *nsec);

    static void
    populate_list(SerialList *list, std::vector<Operation> *gen, int population, int num_ops, int ins_f, int del_f);
};

#endif //CONCURRENTTHLAB_1_UTIL_H
