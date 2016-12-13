//
// Created by krv on 12/10/16.
//

#include <vector>
#include <cmath>
#include <random>
#include "SerialDriver.h"
#include "Util.h"

using namespace std;

#define GET_TIME(x); if(clock_gettime(CLOCK_MONOTONIC, &(x)) < 0) \
                {perror("clock_gettime(): ");  exit(EXIT_FAILURE);}

void SerialDriver::Drive() {

    struct timespec t0, t1;
    unsigned long sec, nsec;
    int small_sample_size = 10;
    float mean;
    float sd;
    int req_n;
    bool keep_running = false;
    do {
        vector<float> tot_times;
        cout << "Number of samples running : " << small_sample_size << endl;
        for (int i = 0; i < small_sample_size; i++) {
            int num_insert_f = ceil(num_operations * insert_frac);
            int num_delete_f = ceil(num_operations * delete_frac);
            int num_member_f = num_operations - num_insert_f - num_delete_f;
            if (num_member_f < 0) {
                cerr << "Invalid number of member calls calculated" << endl;
                abort();
            }

            SerialList list;
            vector<int> generatedValues; // used to generate unique values
            srand(time(NULL));
            vector<float> times(small_sample_size);
            populate_list(&list, &generatedValues, num_population);GET_TIME(t0);
            for (int j = 0; j < num_operations; j++) { // 10000 operation
                int randi = rand() % 3;
                int rand_num = rand() % 65534 + 1;

                switch (randi) {
                    case 0:
                        if (num_insert_f > 0) {
                            list.Insert(rand_num);
                            num_insert_f--;
                        }
                        break;
                    case 1:
                        if (num_delete_f > 0) {
                            list.Delete(rand_num);
                            num_delete_f--;
                        }
                        break;
                    case 2:
                        if (num_member_f > 0) {
                            list.Member(rand_num);
                            num_member_f--;
                        }
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
        cout << "Mean\t : " << mean << " ms" << endl;
        cout << "SD\t\t : " << sd << " ms" << endl;
        cout << "req N\t : " << req_n << " samples" << endl;
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

void SerialDriver::populate_list(SerialList *list, vector<int> *gen, int population) {
    while (list->Size() < population) {
        //int number = rand()%65535+1; // (0, 65535) exclusive range
        int number = rand() % 65534 + 1; // (0, 65535) exclusive range
        if (list->Member(number)) {
            continue;
        }
        list->Insert(number);
        gen->push_back(number);
    }
}

SerialDriver::SerialDriver(float member_f, float insert_f, float delete_f) {
    this->member_frac = member_f;
    this->insert_frac = insert_f;
    this->delete_frac = delete_f;
}
