#include <iostream>
using namespace std;

struct node{
    int elem;
    node* next;
};

class CircularLinkedlist{
    public:
    node* head;
    node* tail;
    int size;

    CircularLinkedlist(): head(nullptr), tail(nullptr), size(0){}

    void add(int num){
        node* newnode = (node*) calloc(1,sizeof(1));
        newnode->elem = num;

        if(head == nullptr){
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

    int remove(int num){
        node* rem;
        int r;

        if(head->elem == num){
            size--;
            if(size == 0){
                r = head->elem;
                head = nullptr;
                tail = nullptr;
                return r;
            }

            rem = head;
            r = head->elem;
            //free(rem);
            head = head->next;
            tail->next = head;
            return r;
        }

        node* temp = head;
        while(temp->next != head){
            if(temp->next->elem == num){
                r = temp->next->elem;
                if(temp->next == tail){
                    temp->next = head;
                } else {
                    temp->next = temp->next->next;
                }

                size--;
                return r;
            }

            temp = temp->next;
        }
    }

    void contain(int left, int right){
        if(left == 0 && right == 0) return;

        node* start = head;
        node* end = head;
        if(left == 0){
            for(int i = 1; i < right; i++){
                end = end->next;
            }

            head = end;
            tail->next = head;

        } else if(right == 0){
            for(int i = 1; i < left; i++){
                start = start->next;
            }

            tail = start;
            tail->next = head;
        } else {
            for(int i = 1; i < left; i++){
                start = start->next;
            }

            for(int i = 1; i < right; i++){
                end = end->next;
            }

            start->next = end;
        }
    }

    int retain(int num){
        node* curr = head;
        node* prev = nullptr;

        int ctr = 0;

        do{

            if(curr->elem >= num){
                if(prev == nullptr){
                    prev = curr;
                    head = prev;
                } else {
                    
                    if(curr == tail){
                        prev = curr;
                        tail = prev;
                        prev->next = head;
                        return ctr++;
                    } 

                    prev->next = curr;
                    prev = prev->next;
                }
            } else {
                size--;
                ctr++;
                if(size <= 0){
                    head = nullptr;
                    tail = nullptr;
                    return ctr;
                } 

            }

            curr = curr->next;

        } while(curr != head);

        tail = prev;
        prev->next = head;

        return ctr;
    }

    void print(){
        if(!head) return;
        node* temp = head;
        cout << "List: ";
        do{
            cout << temp->elem << " ";
            temp = temp->next;
        }while(temp != head);
        cout << endl;
    }

    void print(node* temp, node* head){
        if(head == nullptr) return;

        cout << temp->elem << " ";

        if(temp->next == head) return;

        print(temp->next, head);
    }

};

int main(){
    CircularLinkedlist* list = new CircularLinkedlist();
    char op;
    int num, left, right;

    do{

        cout << "Enter option: ";
        cin >> op;

        switch(op){
            case 'a':
                cin >> num;
                list->add(num);
                break;
            case 'x':
                cin >> num;
                cout << "Removed: " << list->remove(num) << endl;
                break;
            case 'c':
                cout << "Left: ";
                cin >> left;

                cout << "Right: ";
                cin >> right;

                list->contain(left,right);
                break;
            case 'r':
                list->print(list->head, list->head);
                cout << endl;
                break;
            case '!':
                cin >> num;
                cout << "Removed: " << list->retain(num) << endl;
                break;
            case 'p':
                list->print();
                break;
        }

    }while(op != 'm');
}