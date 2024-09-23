#include <iostream>
using namespace std;

struct node{
    int elem;
    node* next;
};

class List{
    public: 
    virtual void addHead(int num) = 0;
    virtual void addTail(int num) = 0;
    virtual void addAt(int num, int pos) = 0;
    virtual int getPos(int pos) = 0;
    virtual int remove(int num) = 0;
    virtual int removeAt(int pos) = 0;
    virtual int removeAll(int num) = 0;

    virtual void print() = 0;
};

class SinglyLinkedlist : public List{
    node* head;
    node* tail;
    int size;

    public:
    SinglyLinkedlist(): size(0), head(nullptr) , tail(nullptr) {}

    void addHead(int num){
        node* temp = head;
        node* newnode = (node*) calloc(1,sizeof(node*));
        newnode->elem = num;

        if(head == nullptr || size == 0){
            head = newnode;
            tail = newnode;
            size++;
        } else {
            newnode->next = head;
            head = newnode;
            size++;
        }

        return;
    }

    void addTail(int num){

        node* newnode = (node*) calloc(1, sizeof(node**));
        newnode->elem = num;

        if(tail == nullptr || size == 0){
            head = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }

        size++;
        return;
    }

    void addAt(int num, int pos){

        node* newnode = (node*) calloc(1, sizeof(node));
        newnode->elem = num;

        if (pos == 1){
            newnode->next = head;
            head = newnode;
            size++;
            return;
        } else if(pos == size){
            newnode->next = tail;
            tail = newnode;
            size++;
            return;
        }

        node* temp = head;
        int ctr = 1;
        while(temp != nullptr){
            if(ctr == pos - 1){
                newnode->next = temp->next;
                temp->next = newnode;
                size++;
            }

            ctr++;
            temp = temp->next;
        }

        return;
    }

    int getPos(int num){
        node* temp = head;

        if(head->elem == num){
            return 1;
        }

        int ctr = 1;
        while(temp != nullptr){
            if(temp->elem == num){
                return ctr;
            }

            temp = temp->next;
            ctr++;
        }

        return -1;
    }

    int remove(int num){
        node* temp = head;

        if(head->elem == num){
            node* rem = head;
            head = head->next;
            free(rem);
            size--;

                if(size == 0){
                    head = nullptr;
                    tail = nullptr;
                    return 1;
                }
            return 1;
        }

        int ctr = 1;
        while(temp->next != nullptr){
            if(temp->next->elem == num){
                node* rem = temp->next;
                if(temp->next == tail){
                    tail = temp;
                    tail->next = nullptr;
                } else {
                    temp->next = temp->next->next;
                }

                free(rem);
                ctr++;
                size--;
                    if(size == 0){
                        head = nullptr;
                        tail = nullptr;
                        return 1;
                    }
                
                return ctr;
            }

            ctr++;
            temp = temp->next;
        }

        return -1;
    }

    int removeAt(int pos){

        node* curr = head;
        node* prev = nullptr;

        if(size < pos){
            return -1;
        }

        int ctr = 1;
        
        while(ctr <= pos){
            if(ctr == pos){
                int r = curr->elem;
                if(curr == head){
                    //node* rem = head;
                    head = head->next;
                    //free(rem);
                } else {
                    if(curr == tail){
                        //node* rem = tail;
                        tail = prev;
                        //free(rem);
                    }

                    prev->next = curr->next;     
                }

                size--;
                return r;
            }

            prev = curr;
            curr = curr->next;
            ctr++;
        }

        return -1;

        // int rem = getPos(pos);
        // remove(rem);
        // return rem;
    }

    int removeAll(int num){
        int ctr = 0;

        while(remove(num) != -1){
            ctr++;
        }

        return ctr;
    }

    void print(){
        node* temp = head;
        cout << "Size: " << size << endl;
        while(temp != nullptr){
            cout << temp->elem << " ";
            temp = temp->next;
        }

        cout << endl;
        return;
    }


};

int main(){
    List* list = new SinglyLinkedlist();

    int num, pos;
    char op;

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
            case 'a':
                cin >> num;
                cin >> pos;
                list->addAt(num, pos);
                break;
            case 'g':
                cin >> num;
                cout << "Pos: " << list->getPos(num) << endl;
                break;
            case 'r':
                cin >> num;
                cout << "Pos: " << list->remove(num) << endl; 
                break;
            case '@':
                cin >> pos;
                cout << "Removed: " << list->removeAt(pos) << endl;
                break;
            case '#':
                cin >> num;
                cout << "Numbers removed: " << list->removeAll(num) << endl;
                break;
            case 'p':
                list->print();
                break;
        }

    } while(op != 'x');

}