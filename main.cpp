#include <iostream>
#include "SerialList.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    SerialList list;

    list.Insert(5);
    list.Insert(6);
    list.Insert(7);

    list.Print();

    list.Delete(6);
    list.Delete(7);
    list.Delete(5);

    list.Print();

    Node * x = list.Member(7);
    if(x != list.nil){
        cout << x->value << " is a member" << endl;
    }


    Node * y = list.Member(70);
    if(y != list.nil){
        cout << y->value << " is a member" << endl;
    }else{
        cout << "70 is not a member" << endl;
    }
    return 0;
}