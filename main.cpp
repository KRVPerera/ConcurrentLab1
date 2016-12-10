#include <iostream>
#include <unistd.h>
#include <random>
#include "SerialList.h"
#include "MutexList.h"

using namespace std;

#define GET_TIME(x); if(clock_gettime(CLOCK_MONOTONIC, &(x)) < 0) \
                {perror("clock_gettime(): ");  exit(EXIT_FAILURE);}

float elapsed_time_msec(struct timespec *begin, struct timespec *end,
                        unsigned long *sec, unsigned long *nsec);

// N = (100zs/rx)^2, r - accuracy (5%), s - standard deviation, x - mean, z = 1.960 (95%) - TAKE THE CEIL
//TODO (krv) : get the sample size from
int main(int argc, char **argv) {
    // fractions
    float member_frac = 0.50, insert_fract = 0.25, delete_frac = 0.25;
    // Default values
    int num_population = 1000; // n
    int num_operations = 10000; // m
    // Argumetn pasrser variables
    int c;
    opterr = 0;
    // Time variables
    struct timespec t0, t1;
    float comp_time;
    unsigned long sec, nsec;
    // Multi threading variables
    int num_threads = 2;

    // Reading command line arguments
    while ((c = getopt(argc, argv, "n:m:i:d:t:")) != -1) {
        switch (c) {
            case 'n':
                try {
                    num_population = stoi(optarg);
                } catch (std::logic_error) {
                    cerr << "Invalid value for -n, set to 1000" << endl;
                    num_population = 1000;
                }
                break;
            case 'm':
                try {
                    num_operations = stoi(optarg);
                } catch (std::logic_error) {
                    cerr << "Inavlid value for -m, set to 10,000" << endl;
                    num_operations = 10000;
                }
                break;
            case 'i':
                try {
                    insert_fract = stof(optarg);
                } catch (std::logic_error) {
                    cerr << "Inavlid value for -i, set to 0.25" << endl;
                    insert_fract = 0.25;
                }
                break;
            case 't':
                try {
                    num_threads = stoi(optarg);
                } catch (std::logic_error) {
                    cerr << "Inavlid value for -t, set to 2" << endl;
                    num_threads = 2;
                }
                break;
            case 'd':
                try {
                    delete_frac = stof(optarg);
                } catch (std::logic_error) {
                    cerr << "Inavlid value for -d, set to 0.25" << endl;
                    delete_frac = 0.25;
                }
                break;
            case '?':
                if (optopt == 'i') {
                    cerr << "Option -i requires an floating point argument" << endl;
                } else if (optopt == 'd') {
                    cerr << "Option -d requires an floating point argument" << endl;
                } else if (optopt == 'n') {
                    cerr << "Option -n requires an integer argument" << endl;
                } else if (optopt == 'm') {
                    cerr << "Option -m requires an integer argument" << endl;
                } else if (isprint(optopt)) {
                    cerr << "Unknown option -" << optopt << endl;
                } else {
                    cerr << "Unknown option character" << endl;
                }
                return 1;
            default:
                abort();
        }
    }

    // check the total of fractions
    member_frac = 1 - delete_frac - insert_fract;
    if (member_frac < 0) {
        cerr << "Member fraction is negative!" << endl;
        abort();
    }
    time_t seed = time(NULL);
    srand(seed); // seed for each iteration , each test use a one seed
    cout << "Population\t\t-n : " << num_population << endl;
    cout << "Operations\t\t-m : " << num_operations << endl;
    cout << "Operations\t\t-t : " << num_operations << endl;
    cout << "Member fraction\t   : " << member_frac * 100 << "%" << endl;
    cout << "Insert fraction\t-i : " << insert_fract * 100 << "%" << endl;
    cout << "Delete fraction\t-d : " << delete_frac * 100 << "%" << endl;
    cout << "Threads\t\t\t-t : " << num_threads  << endl;
    cout << "Seed\t\t\t   : " << seed  << endl;

    MutexList list;GET_TIME(t0);
    list.Insert(5);
    list.Insert(6);
    cout << "size 2 : " << list.Size() << endl;
    list.Insert(7);
    cout << "size 3 : " << list.Size() << endl;
    list.Print();GET_TIME(t1);
    list.Delete(6);
    list.Delete(5);

    list.Print();

    bool yes = list.Member(7);
    if (yes) {
        cout << 7 << " is a member" << endl;
    }


    yes = list.Member(70);
    if (yes) {
        cout << 70 << " is a member" << endl;
    } else {
        cout << "70 is not a member" <<
             endl;
    }
    comp_time = elapsed_time_msec(&t0, &t1, &sec, &nsec);
    cout << "Elapsed-time(ms) = " << comp_time << endl;
    return 0;
}

float elapsed_time_msec(struct timespec *begin, struct timespec *end,
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