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

        cout << "Number of samples running  : " << small_sample_size << endl;
        for (int i = 0; i < small_sample_size; i++) {
            MutexList list;
            comp_time = ThreadCreation(&list);
            tot_times.push_back(comp_time);
        }
        mean = Util::Mean(tot_times);
        sd = Util::StandardDeviation(tot_times);
        req_n = Util::RequiredSampleSize(sd, mean);
        cout << "Mean\t\t\t   : " << mean << " ms" << endl;
        cout << "SD\t\t\t   : " << sd << " ms" << endl;
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
    this->thread_count = thread_cnt;
    if (thread_count > MAX_THREADS) {
        cerr << "Maximum number of thread is 4. Setting to 4 automatically" << endl;
        thread_count = 4;
    }
}


float MutexDriver::ThreadCreation(MutexList *list) {
    struct timespec tt0, tt1;
    unsigned long sec, nsec;
    float t_comp_time;
    vector<Operation> generatedValues;
    int num_insert_f = ceil(num_operations * insert_frac);
    int num_delete_f = ceil(num_operations * delete_frac);
    int num_member_f = num_operations - num_insert_f - num_delete_f;
    if (num_member_f < 0) {
        cerr << "Invalid number of member calls calculated" << endl;
        abort();
    }
    Util::populate_list((SerialList *) list, &generatedValues, num_population, num_operations, num_insert_f,
                        num_delete_f);

    GET_TIME(tt0)
    pthread_t thread_pool[thread_count];
    thread_data data[thread_count];

    for (int i = 0; i < thread_count; ++i) {
        data[i].tid = i;
        data[i].gen_list = &generatedValues;
        data[i].num_threads = thread_count;
        data[i].list = list;
        pthread_create(&thread_pool[i], NULL, MutexDriver::work, &data[i]);
    }

    for (int i = 0; i < thread_count; ++i) {
        pthread_join(thread_pool[i], NULL);
    }

    GET_TIME(tt1)

    t_comp_time = Util::elapsed_time_msec(&tt0, &tt1, &sec, &nsec);
//    cout << "Time spent : " << t_comp_time << endl;
    return t_comp_time;
}

void *MutexDriver::work(void *data_p) {
    thread_data t_data = *((thread_data *) data_p);
    int my_id = t_data.tid;
    int thread_cnt = t_data.num_threads;
    int op_size = t_data.gen_list->size();
    vector<Operation> *gen_l = t_data.gen_list;
    int start = (my_id * op_size) / thread_cnt;
    int end = ((my_id + 1) * op_size) / thread_cnt;
//    cout << "start : " << start << " end : " << end;
    MutexList *list = t_data.list;

    for (int i = start; i < end; ++i) {
        Operation cur_op = gen_l->at(i);
        int val = cur_op.value;
        Op cur_f = cur_op.op;
        switch (cur_op.op) {
            case Op::Insert:
                list->Insert(val);
                break;
            case Op::Delete:
                list->Delete(val);
                break;
            case Op::Member:
                list->Member(val);
                break;
            default:
                cerr << "Invalid random function call" << endl;
                break;
        }
    }
    pthread_exit(NULL);
}