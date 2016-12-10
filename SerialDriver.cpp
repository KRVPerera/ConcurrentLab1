//
// Created by krv on 12/10/16.
//

#include <vector>
#include "SerialDriver.h"

using namespace std;

void SerialDriver::Drive() {
    SerialList list;
    vector<float> times;
    for (int i = 0; i < 10; i++) {

    }
}

void SerialDriver::populate_list(SerialList *list, int population) {
    while (list->Size() < population) {
        //int number = rand()%65535+1; // (0, 65535) exclusive range
        int number = rand() % 65534 + 1; // (0, 65535) exclusive range
        if (list->Member(number)) {
            continue;
        }
        list->Insert(number);
    }
}