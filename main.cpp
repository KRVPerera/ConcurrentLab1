#include <iostream>
#include <unistd.h>
#include "SerialList.h"

using namespace std;

int main(int argc, char **argv) {
    // fractions
    float member_frac = 0.50, insert_fract = 0.25, delete_frac = 0.25;
    // Default values
    int num_population = 1000; // n
    int num_operations = 10000; // m
    // Argumetn pasrser variables
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "n:m:i:d:")) != -1) {
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

    member_frac = 1 - delete_frac - insert_fract;


    cout << "Population   : " << num_population <<
         endl;
    cout << "Operations   : " << num_operations <<
         endl;
    cout << "Memeber frac : " << member_frac * 100 << "%" <<
         endl;
    cout << "Insert frac  : " << insert_fract * 100 << "%" <<
         endl;
    cout << "Delete frac  : " << delete_frac * 100 << "%" <<
         endl;

    SerialList list;

    list.Insert(5);
    list.Insert(6);
    list.Insert(7);

    list.

            Print();

    list.Delete(6);
    list.Delete(5);

    list.

            Print();

    bool yes = list.Member(7);
    if (yes) {
        cout << 7 << " is a member" <<
             endl;
    }


    yes = list.Member(70);
    if (yes) {
        cout << 70 << " is a member" <<
             endl;
    } else {
        cout << "70 is not a member" <<
             endl;
    }
    return 0;
}