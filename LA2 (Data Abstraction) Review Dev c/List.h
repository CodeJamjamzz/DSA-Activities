#include <iostream>

class List {
public:
    virtual void add(int num) = 0;
    virtual void print() = 0;
    virtual int removeAtpos(int pos) = 0;
    virtual int removeAll(int num) = 0;
    virtual void addAtpos(int pos, int num) = 0;
    
    virtual void flip() = 0; 
//  virtual void plus(int num) = 0; niya e add ang num to every element sa array
//	virtual int summation() = 0; total sa array mao to ako na remember hehe 
};
