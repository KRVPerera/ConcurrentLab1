//
// Created by krv on 12/13/16.
//

#ifndef CONCURRENTTHLAB_1_COMMON_H
#define CONCURRENTTHLAB_1_COMMON_H

typedef struct Operation{
    int value; // value to be used in the operation
    Op op; // 0 - Insert,
}Operation;

enum Op {
    Insert,
    Delete,
    Member
};
#endif //CONCURRENTTHLAB_1_COMMON_H
