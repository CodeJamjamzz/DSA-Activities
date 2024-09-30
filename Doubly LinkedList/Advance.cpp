#include <iostream>
using namespace std;

struct node{
    int elem;
    node* prev, *next;
};

class List {
    public:
    virtual void addhead(int num) = 0;
    virtual void print() = 0;
    virtual void addtail(int num) = 0;
    virtual int remove(int num) = 0;
    virtual int removeAt(int pos) = 0;

    virtual void sort() = 0;
    virtual void swapAdjacent() = 0;
};

class DoublyLinkedList : public List {
    node* head;
    node* tail;
    int size;

    public:
    DoublyLinkedList(): head(nullptr), tail(nullptr), size(0){}

    void addhead(int num){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->elem = num;

        if(head == nullptr){
            head = newnode;
            tail = newnode;
            size++;
        } else {
            head->prev = newnode;
            newnode->next = head;
            head = newnode;
            size++;
        }
    }   

    void addtail(int num){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->elem = num;

        if(tail == nullptr){
            head = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }

        size++;
    }

    int remove(int num){

        if(head->elem == num){
            size--;
            if(size == 0){
                head = nullptr;
                tail = nullptr;
                free(head);
                return 1;
            }

            node* rem = head;

            head = head->next;
            head->prev = nullptr;

            free(rem);
            return 1;
        }

        node* temp = head;
        int pos = 2;
        while(temp != nullptr && temp->next != nullptr){
            if(temp->next->elem == num){
                if(temp->next == tail){
                    node* rem = tail;
                    tail = tail->prev;
                    tail->next = nullptr;

                    size--;
                    free(rem);
                    return pos;
                } else {
                    node* rem = temp->next;
                    node* next = temp->next->next;

                    next->prev = temp;
                    temp->next = next;

                    free(rem);
                    size--;
                    return pos;
                }
            }
            
            pos++;
            temp = temp->next;
        }

        return -1;

    }

    int removeAt(int pos){
        int ctr = 1;
        node* curr = head;
        node* prev = nullptr;

        // if(size < pos){
        //     return -1;
        // }

        while(ctr <= size){
            
            if(ctr == pos){
                if(curr == head){
                    size--;
                    if(size == 0){
                        int r = head->elem;
                        node* rem = head;
                        head = nullptr;
                        tail = nullptr;

                        free(rem);
                        return r;
                    }

                    node* rem = head;
                    int r = head->elem;
                    head = head->next;
                    head->prev = nullptr;
                    free(rem);
                    return r;
                } else if (curr == tail){
                    node* rem = tail;
                    int r = tail->elem;
                    prev->next = nullptr;
                    tail = prev;
                    
                    free(rem);
                    return r;
                } else {
                    int r = curr->elem;
                    prev->next = curr->next;
                    curr->next->prev = prev;
                    free(curr);
                    return r;
                }
            } 

            ctr++;
            prev = curr;
            curr = curr->next;
        }

        return -1;
    }

    node* swap(node* node1, node* node2){
        if(node1->elem == node2->elem || node1 == nullptr || node2 == nullptr){
            return nullptr;
        }

        if(node1->prev != nullptr){
            node1->prev->next = node2;
        } else {
            head = node2;
        }

        if (node2->next != nullptr) {
            node2->next->prev = node1;
        } else {
            tail = node1;
        }

        node1->next = node2->next;
        node2->prev = node1->prev;
        node1->prev = node2;
        node2->next = node1;

        return node1->next;
    }

    void sort() {
        bool swapped;

        do{
            swapped = false;
            node* temp = head;

            while(temp->next != nullptr){
                if(temp->elem > temp->next->elem){
                    swap(temp, temp->next);
                    swapped = true;
                }

                temp = temp->next;
            }

        } while (swapped);

        return;
    }

    void swapAdjacent(){
        node* temp = head;
        node* ret;


        while(temp != nullptr && temp->next != nullptr){
                ret = swap(temp, temp->next);
                temp = ret;
        }
    }

    void print(){
        cout << "From Head -> Tail: " << endl;
        node* temp = head;
        while(temp != nullptr){
            cout << temp->elem;

            if(temp->next != nullptr){
                cout << " -> ";
            }

            temp = temp->next;
        }

        cout << endl;

        cout << "From Tail -> Head: " << endl;
        temp = tail;
        while(temp != nullptr){
            cout << temp->elem;
            if(temp->prev != nullptr){
                cout << " <- ";
            }
            
            temp = temp->prev;
        }

        cout << endl;
    }
};

int main(){
    List* list = new DoublyLinkedList();
    char op;
    int num, pos;

    do{

        cout << "Enter option: ";
        cin >> op;

        switch(op){
            case 'h':
                cin >> num;
                list->addhead(num);
                break;
            case 't':
                cin >> num;
                list->addtail(num);
                break;
            case 'r':
                cin >> num;
                cout << "Pos Removed: " << list->remove(num) << endl;
                break;
            case '#':
                cin >> pos;
                cout << "Number Removed: " << list->removeAt(pos) << endl;
                break;
            case 's':
                list->sort();
                break;
            case '*':
                list->swapAdjacent();
                break;
            case 'p':
                list->print();
                break;
        }

    } while(op != 'x');
}