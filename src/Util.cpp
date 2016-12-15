//
// Created by krv on 12/10/16.
//

#include <cmath>
#include "../include/Util.h"
#include <algorithm>
#include <cassert>

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
    float sum;
    sum = accumulate(times.begin(), times.end(), 0);
    return (float) sum / size;
}

float Util::StandardDeviation(vector<float> times) {
    double mean = Util::Mean(times);
    double variance = 0;
    for (int i = 0; i < times.size(); ++i) {
        variance += pow(times.at(i) - mean, 2);
    }
    variance = variance / times.size();
    return sqrt(variance);
}

float Util::elapsed_time_nsec(struct timespec *begin, struct timespec *end,
                              unsigned long *sec, unsigned long *nsec) {
    if (end->tv_nsec < begin->tv_nsec) {
        *nsec = 1000000000 - (begin->tv_nsec - end->tv_nsec);
        *sec = end->tv_sec - begin->tv_sec - 1;
    } else {
        *nsec = end->tv_nsec - begin->tv_nsec;
        *sec = end->tv_sec - begin->tv_sec;
    }
    return (float) (*sec) * 1000000 + ((float) (*nsec));
}


float Util::elapsed_time_microsec(struct timespec *begin, struct timespec *end,
                                  unsigned long *sec, unsigned long *nsec) {
    if (end->tv_nsec < begin->tv_nsec) {
        *nsec = 1000000000 - (begin->tv_nsec - end->tv_nsec);
        *sec = end->tv_sec - begin->tv_sec - 1;
    } else {
        *nsec = end->tv_nsec - begin->tv_nsec;
        *sec = end->tv_sec - begin->tv_sec;
    }
    return (float) (*sec) * 1000000 + ((float) (*nsec)) / 1000.0;
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

void
Util::populate_list(SerialList *list, vector<Operation> *gen, int population,
                    int num_ops, int ins_f, int del_f) {
    srand(time(NULL));
    while (list->Size() < population) {
        //int number = rand()%65535+1; // (0, 65535) exclusive range
        int number = rand() % 65534 + 1; // (0, 65535) exclusive range
        if (list->Member(number)) {
            continue;
        }
        list->Insert(number);
    }

    int num_insert_f = ins_f;
    assert(("No Inserts ", num_insert_f > 0));
    int num_delete_f = del_f;
    assert(("No Deletes ", num_delete_f > 0));
    int num_member_f = num_ops - num_insert_f - num_delete_f;
    if (num_member_f <= 0) {
        cerr << "Invalid number of member calls calculated" << endl;
        abort();
    }

    for (int i = 0; i < num_ops; ++i) {
        int opNumber = rand() % 65534 + 1;
        int func = rand() % 3;
        Operation new_op;
        new_op.value = opNumber;
        bool op_fail = false;
        switch (func) {
            case 0:
                if (num_insert_f > 0) {
                    new_op.op = Op::Insert;
                    num_insert_f--;
                    if (!gen->empty()) {
                        for (int j = gen->size() - 1; j >= 0; --j) {
                            if (new_op.value == gen->at(j).value) {
                                if (gen->at(j).op == Op::Insert) {
                                    op_fail = true;
                                    num_insert_f++;
                                    break;
                                } else if (gen->at(j).op == Op::Delete) {
                                    op_fail = false;
                                    break;
                                }
                            }
                        }
                    }
                } else {
                    op_fail = true;
                }
                break;
            case 1:
                if (num_delete_f > 0) {
                    new_op.op = Op::Delete;
                    num_delete_f--;
                    op_fail = false;
                } else {
                    op_fail = true;
                }
                break;
            case 2:
                if (num_member_f > 0) {
                    new_op.op = Op::Member;
                    num_member_f--;
                    op_fail = false;
                } else {
                    op_fail = true;
                }
                break;
            default:
                cerr << "Invalid random function call" << endl;
                break;
        }


        if (op_fail) {
            i--;
        } else {
            gen->push_back(new_op);
        }
    }
    assert(("Ops length error ", gen->size() == num_ops));

}