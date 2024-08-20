#include <iostream>
#include "ArrayList.h"
using namespace std;

int main(){
    List* list = new ArrayList();
    
    list->add(2);
    list->add(4);
    list->add(5);
    list->add(2);
    list->add(2);
    
    list->print();
    
    cout << "Remove at pos 2: " << list->removeAtpos(2) << endl;
    list->print();
    
    cout << "Remove all 2 numbers: " << list->removeAll(2) << endl;
    list->print();
    
    list->add(4);
    list->add(3);
//    list->add(2);
//    list->add(1);
    list->print();
    list->flip();
    list->print();
    
    list->addAtpos(2, 2);
    list->addAtpos(1, 9);
    list->print();
}
