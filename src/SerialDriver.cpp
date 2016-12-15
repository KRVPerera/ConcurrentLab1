//
// Created by krv on 12/10/16.
//

#include <vector>
#include <cmath>
#include <random>
#include "../include/SerialDriver.h"
#include "../include/Util.h"

using namespace std;

#define GET_TIME(x); if(clock_gettime(CLOCK_MONOTONIC, &(x)) < 0) \
                {perror("clock_gettime(): ");  exit(EXIT_FAILURE);}

void SerialDriver::Drive() {

    struct timespec t0, t1;
    unsigned long sec, nsec;
    int small_sample_size = 100;
    float mean;
    float sd;
    int req_n;
    bool keep_running;

    int num_insert_f = ceil(num_operations * insert_frac);
    int num_delete_f = ceil(num_operations * delete_frac);
    int num_member_f = num_operations - num_insert_f - num_delete_f;
    if (num_member_f < 0) {
        cerr << "Invalid number of member calls calculated" << endl;
        abort();
    }

    do {
        vector<float> tot_times;
        cout << "Number of samples running  : " << small_sample_size << endl;
        for (int i = 0; i < small_sample_size; i++) {
            // Change the seed for this sample
            vector<Operation> generatedValues; // used to generate unique values
            SerialList list;
            Util::populate_list(&list, &generatedValues, num_population, num_operations, num_insert_f, num_delete_f);
            GET_TIME(t0);
            for (int j = 0; j < num_operations; j++) { // 10000 operation
                Operation cur_op = generatedValues[j];
                int val = cur_op.value;
                switch (cur_op.op) {
                    case Op::Insert:
                        list.Insert(val);
                        break;
                    case Op::Delete:
                        list.Delete(val);
                        break;
                    case Op::Member:
                        list.Member(val);
                        break;
                    default:
                        cerr << "Invalid random function call" << endl;
                        break;
                }
            }GET_TIME(t1);
            float sum_time = Util::elapsed_time_msec(&t0, &t1, &sec, &nsec);
            tot_times.push_back(sum_time);
        }
        mean = Util::Mean(tot_times);
        sd = Util::StandardDeviation(tot_times);
        req_n = Util::RequiredSampleSize(sd, mean);
        cout << "Mean\t\t\t   : " << mean << " ms" << endl;
        cout << "SD\t\t\t   : " << sd << " ms" << endl;
        cout << "Range\t\t\t   : " << mean - sd << " - " << mean + sd << endl;
        cout << "req N\t\t\t   : " << req_n << " samples" << endl;
        if (req_n > small_sample_size) {
            cerr << "Need to run " << req_n - small_sample_size << " more iterations" << endl;
            cout << "Starting again..." << endl;
            small_sample_size = req_n;
            keep_running = true;
        } else {
            keep_running = false;
        }

        tot_times.resize(0);
        tot_times.resize(10);
    } while (keep_running);

}

SerialDriver::SerialDriver(float member_f, float insert_f, int pop, int ops) {
    this->member_frac = member_f;
    this->insert_frac = insert_f;
    this->delete_frac = 1 - member_f - insert_f;
    this->num_population = pop;
    this->num_operations = ops;
}

