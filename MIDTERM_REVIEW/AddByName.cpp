#include <iostream>
#include <cmath>
using namespace std;

struct Person{
    string name;
    int age;
    string course;
};

class List{
    Person** array;
    int capacity;
    int size;
    int senior;

    public:
    List(int num): capacity(num){
        senior = 0;
        size = 0;
        array = (Person**) calloc(capacity, sizeof(Person*));
    }

    void addbyName(Person* student){

        if(size == capacity){
            capacity = ceil(capacity * 1.5);
            array = (Person**) realloc(array, capacity * sizeof(Person*));
        }

        int i;
        for(i = 0; i < size; i++){
            if(array[i]->name > student->name){
                break;
            }
        }

        for(int j = size; j > i; j--){
            array[j] = array[j-1];
        }

        array[i] = student;
        size++;
        return;
    }

    void addbyAge(Person* person){
        if(size == capacity){
            capacity = ceil(capacity * 1.5);
            array = (Person**) realloc(array, capacity * sizeof(Person*));
        }

        bool flag = false;
        int i;
        for(i = 0; i < size; i++){
            if(array[i]->age < 60){
                flag = true;
                break;
            }
        }

        if(flag){
            for(int j = size; j > i; j--){
                array[j] = array[j-1];
            }  
        } else {
            array[size++] = person;
            return;
        }
        
        array[i] = person;
        senior++;
        size++;
        return;
    }

    void print(){

        cout << "Size: " << size << "/" << capacity << endl;
        for(int i = 0; i < size; i++){
            cout << array[i]->name << " " << array[i]->age << endl;
        }

        cout << endl;
    }
};

int main(){

    List* list = new List(5);
    Person* student;
    Person* senior;
    char op;

    do{
        
        cout << "Enter option: ";
        cin >> op;

        switch(op){
            case 'a':
                student = new Person;
                
                cout << "Enter name: ";
                cin >> student->name;

                cout << "Enter age: ";
                cin >> student->age;

                list->addbyName(student);
                break;
            case '#':
                senior = new Person;
                
                cout << "Enter name: ";
                cin >> senior->name;

                cout << "Enter age: ";
                cin >> senior->age;

                list->addbyAge(senior);
                break;
            case 'p':
                list->print();
                break;
        }
        
        
    }while(op != 'x');
}