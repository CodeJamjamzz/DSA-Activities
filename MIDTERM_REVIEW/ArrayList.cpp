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
    Person** cheaters;

    int size2;
    int capacity2;

    public:
    List(int num): capacity(num){
        senior = 0;
        size = 0;
        capacity = 5;
        array = (Person**) calloc(capacity, sizeof(Person*));

        size2 = 0;
        capacity2 = 5;
        cheaters = (Person**) calloc(capacity, sizeof(Person*));
        
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

    string removeAt(int pos){
        for(int i = 0; i < size; i++){
            if(i == pos - 1){
                string rem = array[i]->name;
                free(array[i]);
                for(int j = i; j < size; j++){
                    array[j] = array[j+1];
                }
                size--;


                if(size <= capacity / 2.0){

                    capacity = ceil(capacity * 0.25);

                    if(capacity < 5){
                        capacity = 5;
                    } else {
                        array = (Person**) realloc(array, capacity * sizeof(Person**));
                    }
                }

                return rem;
            }
        }

        return "";
    }

    void addCheaters(Person* p){
        if(size == capacity2){
            capacity2 = ceil(capacity2 * 1.5);
            cheaters = (Person**) realloc(cheaters, capacity2 * sizeof(Person*));
        }

        cheaters[size2++] = p;
        return;
    }

    // void removeCheaters(string name){
    //     for(int i = 0; i < size; i++){
    //         for(int j = 0; j < size2; j++){
    //             if()
    //         }
    //     }
    // }

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
    int num;
    char op;

    do{
        
        cout << "Enter option: ";
        cin >> op;

        switch(op){
            // case 'a':
            //     student = new Person;
                
            //     cout << "Enter name: ";
            //     cin >> student->name;

            //     cout << "Enter age: ";
            //     cin >> student->age;

            //     list->addbyName(student);
            //     break;
            case '#':
                senior = new Person;
                
                cout << "Enter name: ";
                cin >> senior->name;

                cout << "Enter course: ";
                cin >> senior->course;

                cout << "Enter age: ";
                cin >> senior->age;

                list->addbyAge(senior);
                break;
            case '@':
                cin >> num;
                list->removeAt(num);
                break;
            case 'p':
                list->print();
                break;
        }
        
        
    }while(op != 'x');
}