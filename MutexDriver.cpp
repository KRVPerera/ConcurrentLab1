//
// Created by krv on 12/11/16.
//

#include "MutexList.h"
#include "MutexDriver.h"
#include <cmath>
#include <random>
#include "Util.h"

using namespace std;

#define GET_TIME(x); if(clock_gettime(CLOCK_MONOTONIC, &(x)) < 0) \
                {perror("clock_gettime(): ");  exit(EXIT_FAILURE);}

void MutexDriver::Drive() {

    int small_sample_size = 10;
    float comp_time;
    float mean;
    float sd;
    int req_n;
    bool keep_running;
    vector<float> tot_times;
    do {

        cout << "Number of samples running : " << small_sample_size << endl;
        for (int i = 0; i < small_sample_size; i++) {
            MutexList list;
            std::vector<int> generatedValues;
            populate_list(&list, &generatedValues, num_population);
            comp_time = ThreadCreation(&list);
            tot_times.push_back(comp_time);

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


void MutexDriver::populate_list(MutexList *list, std::vector<int> *gen, int population) {
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

MutexDriver::MutexDriver(float member_f, float insert_f, float delete_f, int thread_cnt) {
    this->member_frac = member_f;
    this->insert_frac = insert_f;
    this->delete_frac = delete_f;
    this->THREAD_COUNT = thread_cnt;
    if (THREAD_COUNT > MAX_THREADS) {
        cerr << "Maximum number of thread is 4. Setting to 4 automatically" << endl;
        THREAD_COUNT = 4;
    }
}


float MutexDriver::ThreadCreation(MutexList *list) {
    struct timespec tt0, tt1;
    unsigned long sec, nsec;
    float t_comp_time;GET_TIME(tt0)
    pthread_t thread_pool[THREAD_COUNT];
    int myid[THREAD_COUNT];
    thread_data data[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i) {
        data[i].tid = i;
        data[i].insert_f = insert_frac;
        data[i].del_f = delete_frac;
        data[i].tot_loc_operations = num_operations / THREAD_COUNT;
        data[i].mem_f = member_frac;
        data[i].list = list;
        pthread_create(&thread_pool[i], NULL, MutexDriver::work, &data[i]);
    }
    for (int i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(thread_pool[i], NULL);
    }GET_TIME(tt1)
    t_comp_time = Util::elapsed_time_msec(&tt0, &tt1, &sec, &nsec);
    cout << "Time spent : " << t_comp_time << endl;
    return t_comp_time;
}

void *MutexDriver::work(void *tid) {
    thread_data tdata = *((thread_data *) tid);
    int tot_local_operations = 10000 / 4; // because 10,000 divided by 4 not considering
    // cases where some counts get rounded and total sum it not equal to THREAD_COUNT
//    int start = (myid * num_operations)/THREAD_COUNT;
//    int end = ((myid+1) * num_operations)/THREAD_COUNT;
    MutexList *list = tdata.list;
    struct timespec t0, t1;
    unsigned long sec, nsec;
    float loc_comp_time = 0;

    int num_insert_f = ceil(tot_local_operations * tdata.insert_f);
    int num_delete_f = ceil(tot_local_operations * tdata.del_f);
    int num_member_f = tot_local_operations - num_insert_f - num_delete_f;
    if (num_member_f < 0) {
        cerr << "Invalid number of member calls calculated" << endl;
        abort();
    }

    for (int i = 0; i < tot_local_operations; ++i) {
        int randi = rand() % 3;
        int rand_num = rand() % 65534 + 1;
        switch (randi) {
            case 0:
                if (num_insert_f > 0) {
                    list->Insert(rand_num);
                    num_insert_f--;
                }
                break;
            case 1:
                if (num_delete_f > 0) {
                    list->Delete(rand_num);
                    num_delete_f--;
                }
                break;
            case 2:
                if (num_member_f > 0) {
                    list->Member(rand_num);
                    num_member_f--;
                }
                break;
            default:
                cerr << "Invalid random function call" << endl;
                break;
        }
    }
    pthread_exit(NULL);
}