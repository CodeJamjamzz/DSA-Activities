#include <iostream>
using namespace std;

struct node{
    int elem;
    node* next;
    node* prev;
};

class List{
    node* head;
    node* tail;
    int size;

    public:
    List(): head(nullptr), tail(nullptr), size(0){}

    void addHead(int num){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->elem = num;

        if(!head){
            head = newnode;
            tail = newnode;
            tail->next = head;
            tail->prev = head;
            head->prev = tail;
        } else {
            newnode->next = head;
            head = newnode; 
            head->prev = tail;
            tail->next = head;
        }

        size++;
        return;
    } 

    void remove(int num){
        
    }

    void addTail(int num){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->elem = num;

        if(!tail){
            head = newnode;
            tail = newnode;
            tail->next = head;
            tail->prev = head;
            head->prev = tail;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
            tail->next = head;
        }

        size++;
        return;
    }

    void print(){
        node* temp = head;

        do {
            cout << temp->elem << " ";
            temp = temp->next;
        } while(temp != head);

        cout << endl;
    }
    
};

int main(){
    List* list = new List();
    char op;
    int num, left, right;

    do{

        cout << "Enter option: ";
        cin >> op;

        switch(op){
            case 'h':
                cin >> num;
                list->addHead(num);
                break;
            case 't':
                cin >> num;
                list->addTail(num);
                break;
            case 'p':
                list->print();
                break;
        }

    }while(op != 'm');
}