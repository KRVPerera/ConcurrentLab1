#include <iostream>
#include <unistd.h>
#include <random>
#include "SerialDriver.h"
#include "MutexDriver.h"

using namespace std;

#define GET_TIME(x); if(clock_gettime(CLOCK_MONOTONIC, &(x)) < 0) \
                {perror("clock_gettime(): ");  exit(EXIT_FAILURE);}


#define POPULATION_MAX 65534 // from 1 : 2**16 - 1 (65535)


int main(int argc, char **argv) {
    // fractions
    float member_frac = 0.50, insert_frac = 0.25, delete_frac = 0.25;
    // Default values
    int num_population = 1000; // n
    int num_operations = 10000; // m
    // Argument parser variables
    int c;
    opterr = 0;
    // Time variables
    struct timespec t0, t1;
    float comp_time;
    unsigned long sec, nsec;
    // Multi threading variables
    int num_threads = 2;
    bool serial, mutexed, rwlocked;
    serial = mutexed = rwlocked = false;
    // Reading command line arguments
    while ((c = getopt(argc, argv, "n:m:i:d:t:sg")) != -1) {
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
                    insert_frac = stof(optarg);
                } catch (std::logic_error) {
                    cerr << "Inavlid value for -i, set to 0.25" << endl;
                    insert_frac = 0.25;
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
            case 's':
                serial = true;
                break;
            case 'g':
                mutexed = true;
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
    member_frac = 1 - delete_frac - insert_frac;
    if (member_frac < 0) {
        cerr << "Member fraction is negative!" << endl;
        abort();
    } else if (num_population >= POPULATION_MAX) { // because list has unique values, cannot exceed POPULATION_MAX
        cerr << "Population MAX is " << POPULATION_MAX << endl;
        abort();
    }


    time_t seed = time(NULL);
    srand(seed); // seed for each iteration , each test use a one seed
    cout << "Population\t\t-n : " << num_population << endl;
    cout << "Operations\t\t-m : " << num_operations << endl;
    cout << "Operations\t\t-t : " << num_operations << endl;
    cout << "Member fraction\t   : " << member_frac * 100 << "%" << endl;
    cout << "Insert fraction\t-i : " << insert_frac * 100 << "%" << endl;
    cout << "Delete fraction\t-d : " << delete_frac * 100 << "%" << endl;
    cout << "Threads\t\t\t-t : " << num_threads  << endl;
    cout << "Seed\t\t\t   : " << seed  << endl;

    if (serial) {
        cout << "Serial\t\t\t   : ON" << endl;
        SerialDriver s_drive(member_frac, insert_frac, delete_frac);
        s_drive.Drive();
    }

    if (mutexed) {
        cout << "Mutex\t\t\t   : ON" << endl;
        MutexDriver m_drive(member_frac, insert_frac, delete_frac);
        m_drive.Drive();
    }


    return 0;
}




