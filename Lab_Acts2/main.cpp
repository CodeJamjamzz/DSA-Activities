
/*
    so basically mao ni ang lisod na activity sa among DSA
    naa mi e compare na 2 ka list and dapar buhaton ni nimo
    whitout knowing or using the size of the 2 list kay ang list 
    abstract class raman imo ma acces so dapat kabaw ka mo use aning 
    mga methods. og ayaw kapalaw na optional ang removeAt kay useful kaayo
    siya sa activity.
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class List{
    public:
    virtual void add(int num) = 0;
    virtual int remove(int num) = 0;
    // virtual int get(int pos) = 0;
    virtual void combine(List* list) = 0;
    virtual int removeAt(int pos) = 0;
    virtual bool isEmpty() = 0;
    virtual void print() = 0;
};

class Arraylist : public List{
    int size;
    int capacity;
    int *array;

    public:
    Arraylist(){
        size = 0;
        capacity = 5;
        array = (int*) calloc(capacity , sizeof(int));
    }

    // mo increase ang size of the array evertime ma full siya
    // mo gawas ni siya sa act 1 
    void add(int num){
        if(size == capacity){
            capacity += ceil(capacity / 2.0);
            array = (int*) realloc( array ,capacity * sizeof(int));
        }

        array[size++] = num;
    }

    // mo gawas sa act 1. kalimot ko sa instructions basta inani ang logic hehe
    int remove(int num){
        int rem;
        for(int i = 0; i < size; i++){
            if(num == array[i]){
                rem = array[i];
                for(int j = i; j < size - 1; j++){
                    array[j] = array[j + 1];
                }

                size--;
                break;
            }
        }
        
        // depende ni siya sa instructions
        // nakalimot ko huhu basta same2 rag logic
        if(size <= floor(capacity * 2.0 / 3.0)){
            capacity -= floor(capacity * 0.25);

            if(capacity < 5){
                capacity = 5;
            } else {
                array = (int*) realloc(array, capacity * sizeof(int));
            }
        }

        return rem;
    }

    int removeAt(int pos){
        int rem;
        for(int i = 0; i < size; i++){
            if(i == pos - 1){
                rem = array[i]; // take note ni siya hehe sa act 2
                for(int j = i; j < size - 1; j++){
                    array[j] = array[j + 1];
                }

                size--;
                break;
            }
        }
        
        // depende ni siya sa instructions
        // nakalimot ko huhu basta same2 rag logic
        if(size <= floor(capacity * 2.0 / 3.0)){
            capacity -= floor(capacity * 0.25);

            if(capacity < 5){
                capacity = 5;
            } else {
                array = (int*) realloc(array, capacity * sizeof(int));
            }
        }

        return rem;
    }

    bool isEmpty(){
        return size == 0;
    }

    void combine(List* list){

        while(!list->isEmpty()){
            add(list->removeAt(1));
        }

        // sorry kaayo guys below ani naa pani siya about like sa pag increase sa capacity
        // nakalimot nako sa instruction pero sige lang sayun raman to and e remember lang 
        // kay kanang naa sa taas kay mao na ang importante hehe
    }

    void print(){
        if (size == 0){
            cout << "Nothing left";
            return;
        }
        
        cout << "Array: ";
        for(int i = 0; i < size; i++){
            cout << array[i] << " ";
        }
    }
};

int main(){
    List* list1 = new Arraylist();
    List* list2 = new Arraylist();
    List* curr = list1;

    char op;

    do {
    
        cout << "Enter option: ";
        cin >> op;

        switch (op){
            case 'a':
                int num;
                cout << "Enter number: ";
                cin >> num;

                curr->add(num);
                break;
            case 's':
                (curr == list1)? curr = list2 : curr = list1;
                (curr == list1)? cout << "List 1:" << endl : cout << "List 2:" << endl;
                break;
            case 'c':
                (curr == list1)? curr->combine(list2) : curr->combine(list1);
                break;
            case 'p':
                curr->print();
                cout << endl;
                break;
            case 'x':
                break;
        }
    } while(op != 'x');

}