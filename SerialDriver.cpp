//
// Created by krv on 12/10/16.
//

#include <vector>
#include <cmath>
#include <random>
#include <cassert>
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
            srand(time(NULL)); // Change the seed for this sample
            SerialList list;
            vector<Operation> generatedValues; // used to generate unique values
            populate_list(&list, &generatedValues, num_population, num_operations, num_insert_f, num_delete_f);

            GET_TIME(t0);
            for (int j = 0; j < num_operations; j++) { // 10000 operation
                Operation cur_op = generatedValues[j];
                int val = cur_op.value;
                Op cur_f = cur_op.op;

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

void
SerialDriver::populate_list(LinkedList *list, vector<Operation> *gen, int population,
                            int num_ops, int ins_f, int del_f) {
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

SerialDriver::SerialDriver(float member_f, float insert_f, int pop, int ops) {
    this->member_frac = member_f;
    this->insert_frac = insert_f;
    this->delete_frac = 1 - member_f - insert_f;
    this->num_population = pop;
    this->num_operations = ops;
}

