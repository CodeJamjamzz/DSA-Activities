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
            newnode->next = newnode;
        } else {
            newnode->next = head;
            head = newnode;
            tail->next = head;
        }

        size++;
        return;
    }

    void addLast(int num){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->elem = num;

        if(!tail){
            tail = newnode;
            head = newnode;
            newnode->next = newnode;
        } else {
            newnode->next = head;
            tail->next = newnode;
            tail = newnode;
        }

        return;
    }

    int remove(int num){
        node* temp = head;
        node* prev = nullptr;
        int ctr = 0;

        do{ 
            if(temp->elem == num){
                if(temp == head){
                size--;
                
                    if(size == 0){
                        free(temp);
                        head = nullptr;
                        tail = nullptr;
                        return ctr;
                    }

                    node* r = temp;
                    head = head->next;
                    tail->next = head;

                    free(r);
                    return ctr;
                } else if(temp == tail){
                    node* r = temp;
                    prev->next = head;
                    free(r);
                    size--;
                    return ctr;
                } else {
                    node* r = temp;
                    prev->next = temp->next;
                    free(r);
                    size--;
                    return ctr;
                }
            }

            ctr++;
            prev = temp;
            temp = temp->next;
        }while(temp != head);
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
                list->remove(num);
                break;
            case 'p':
                list->print();
                break;
        }
        
        
    }while(op != 'x');
}