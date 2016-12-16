//
// Created by root on 12/6/16.
//

#ifndef CONCURRENTTHLAB_1_SERIALLIST_H
#define CONCURRENTTHLAB_1_SERIALLIST_H


#include "LinkedList.h"

class SerialList : public LinkedList {
protected:
    Node *Find(int i) override;

public:

    SerialList();

    ~SerialList();

    /// Delete a given int value from the list
    /// \param i value to be removed from the list
    void Delete(int i) override;

    /// Check whether a given int value is in the list
    /// \param i int value to be checked
    /// \return return true if the value is in the list or false otherwise
    bool Member(int i) override;

    /// Insert a value to the list
    /// \param i int value to be inserted into the list
    void Insert(int i) override;

    /// Returns the size of the list
    /// \return int value indicating the number of elements in the list
    int Size() override;

};

#endif //CONCURRENTTHLAB_1_SERIALLIST_H
