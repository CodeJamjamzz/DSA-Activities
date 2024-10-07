#include <iostream>
using namespace std;

struct node{
    int elem;
    node* next;
};

class List{
    node* head;
    node* tail;
    int size;

    public:
    List(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void addFirst(int num){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->elem = num;

        if(!head){
            head = newnode;
            tail = newnode;
            tail->next = nullptr; // Ensure next of tail is nullptr
        } else {
            tail->next = newnode;
            tail = newnode;
        }

        size++;
        return;
    }

    void flip(){
        node* temp = head;
        node* currnext = nullptr;
        node* prev = nullptr;

        tail = temp;
        while(temp != nullptr){
            currnext = temp->next;
            temp->next = prev;
            prev = temp;
            temp = currnext;
        }

        head = prev;
        tail->next = nullptr;

    }

    void print(){

        node* temp = head;
        while(temp != nullptr){
            cout << temp->elem << " ";
            temp = temp->next;
        }

        cout << endl;
    }

};  

int main(){

    List* list = new List();
    int num;
    char op;

    do{
        
        cout << "Enter option: ";
        cin >> op;

        switch(op){
            case 'a':
                cin >> num;
                list->addFirst(num);
                break;
            case 'f':
                list->flip();
                break;
            case 'p':
                list->print();
                break;
        }
        
        
    }while(op != 'x');
}