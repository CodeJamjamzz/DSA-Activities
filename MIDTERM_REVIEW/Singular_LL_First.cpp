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
            tail->next = head;
        } else {
            newnode->next = head;
            head = newnode;
            tail->next = head;
        }

        size++;
    }

    void addLast(int num){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->elem = num;

        if(!tail){
            head = newnode;
            tail = newnode;
            tail->next = head;
        } else {
            tail->next = newnode;
            tail = newnode;
            tail->next = head;
        }

        size++;
        return;
    }

    void rotate(int k){
        if(size <= 1 || k <= 0) return;

        k = k % size;
        if(k == 0) return;

        node* temp = head;
        for(int i = 0; i < size - k - 1; ++i){
            temp = temp->next;
        }

        // for(int i = 0; i < k - 1; ++i){ left
        //     temp = temp->next;
        // }

        tail = temp;
        head = tail->next;
        tail->next = head;
    }

    void print(){

        node* temp = head;
        if(temp == nullptr){
            cout << "Empty" << endl;
            return;
        }

        cout << "Size: " << size << endl;
        do{
            cout << temp->elem << " ";
            temp = temp->next;
        }while(temp != head);

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
            case 'l':
                cin >> num;
                list->addLast(num);
                break;
            case 'r':
                cin >> num;
                list->rotate(num);
                break;
            case 'p':
                list->print();
                break;
        }
        
        
    }while(op != 'x');
}