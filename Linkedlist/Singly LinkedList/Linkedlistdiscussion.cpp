#include <iostream>
using namespace std;

struct node{
    int elem;
    node* next; // needs to be a pointer in order to point to the other node
                // not able to create the same struct within its self & not able to know its size
};


class List {
    public:
    virtual void add(int num) = 0;
    // virtual int remove(int num) = 0;
    // virtual int get(int pos) = 0;
    virtual void print() = 0;
    virtual void removeHead() = 0;
};

class Linkedlist : public List{
    node* head;
    node* tail;
    int size;

    public:
    Linkedlist(): head(nullptr), tail(nullptr), size(0){}

    void add(int num){
        node* newnode = (node*) calloc(1, sizeof(node)); // no longer need the newnode->next = nullptr
        newnode->elem = num;

        if(head == nullptr){
            head = newnode;
            tail = head;
        } else {
            tail->next = newnode;
            tail = newnode;
        }

        size++;
        return;
    }

    void removeHead(){
        node* rem = head;
        head = head->next;

        free(rem);
        size--;
        return;
    }

    void print(){
        node* current = head;

        cout << "Size: " << size << endl;
        while(current){
            cout << current->elem;
            if(current != tail){
                cout << " -> ";
            }

            current = current->next;
        }

        cout << endl;
    }
};

int main(){
    List* list = new Linkedlist();
    //cout << sizeof(node);

    list->add(13);
    list->add(5);
    list->add(2);

    list->print();
}