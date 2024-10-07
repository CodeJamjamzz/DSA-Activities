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

    void addTail(int num){
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
        return;
    }

    int remove(int num){
        node* rem;
        int r;

        if(head->elem == num){
            size--;
            if(size == 0){
                rem = head;
                head = nullptr;
                tail = nullptr;

                free(rem);
                return 1;
            }

            rem = head;
            head = head->next;
            head->prev = nullptr;
            free(rem);
            return 1;
        }

        int ctr = 2;
        node* temp = head;
        while(temp != nullptr && temp->next != nullptr){
            if(temp->next->elem == num){
                if(temp->next == tail){
                    rem = tail;
                    tail = tail->prev;
                    tail->next = nullptr;
                    size--;

                    free(rem);
                    return ctr++;
                } else {
                    rem = temp->next;
                    rem->next->prev = temp;
                    temp->next = temp->next->next;

                    free(rem);
                    size--;
                    return ctr++;
                }
            }

            ctr++;
            temp = temp->next;
        }

        return -1;
    }

    bool isEmpty(){
        return size == 0;
    }

    void combine(List* list){
        while(!list->isEmpty()){
            this->addTail(list->removeAt(1));
        }

        return;
    }

    // int removeAt(int pos){
    //     node* temp = head;
    //     node* prev;
    //     node* rem;
    //     int r;

    //     int ctr = 1;
    //     while(ctr <= size){
    //         if(ctr == pos){
    //             if(temp == head){
    //                 size--;
    //                 if(size == 0){
    //                     rem = head;
    //                     r = head->elem;
    //                     head = nullptr;
    //                     tail = nullptr;

    //                     free(rem);
    //                     return r;
    //                 }

    //                 rem = head;
    //                 r = head->elem;
    //                 head = head->next;
    //                 head->prev = nullptr;

    //                 return r;
    //             } else if (temp == tail){
    //                 size--;
    //                 rem = temp;
    //                 r = temp->elem;
    //                 temp = prev;
    //                 temp->next = nullptr;

    //                 free(temp);
    //                 return r;
    //             } else {
    //                 r = temp->elem;
    //                 rem = temp;
    //                 prev->next = temp->next;
    //                 temp->next->prev = prev;
    //                 size--;

    //                 free(rem);
    //                 return r;
    //             }
    //         }

    //         ctr++;
    //         prev = temp;
    //         temp = temp->next;
    //     }

    //     return -1;
    // }

    int removeAt(int pos){
        
        if(pos > size){
            return -1;
        }
        
        node* curr;
        if(pos < size / 2){
            curr = head;
            for(int i = 1; i <= pos; i++){
                curr = curr->next;
            }
        } else {
            curr = tail;
            for(int i = size - 1; i >= pos; i--){
                curr = curr->prev;
            }
        }
        size--;
        return removeBetween(curr);
    }

    int removeBetween(node* n){
        node* prev = n->prev;
        node* next = n->next;

        if(prev){
            prev->next = next;
        } else {
            head = next;
        }

        if(next){
            next->prev = prev;
        } else {
            tail = prev;
        }

        int rem = n->elem;
        size--;
        free(n);
        return rem;
    }

    int retain(int num){
        node* curr = head;
        node* prev = nullptr;
        int ctr = 0;

        while(curr != nullptr){
            
            if(curr->elem >= num){

                if(prev == nullptr){
                    prev = curr;

                    if(curr == tail){
                        tail = prev;
                        head = prev;
                        return ctr;
                    }

                    head = prev;
                } else {

                    prev->next = curr;
                    curr->prev = prev;
                    prev = prev->next;

                }

            } else {
                size--;
                ctr++;
                if(size == 0 && curr == head) {
                    head = nullptr;
                    tail = nullptr;
                    return ctr;
                } else if (size == 0 && curr == tail){
                    head = nullptr;
                    tail = nullptr;
                    return ctr;
                }
            }

            curr = curr->next;
        }

        tail = prev;
        tail->next = nullptr;
        return ctr;
    }

    int corner(int left, int right){
        node* start = head;
        node* end = tail;
        
        for(int i = 0; i < left; i++){
            start = start->next;
        }

        for(int i = 0; i < right; i++){
            end = end->prev;
        }

        // node* curr = start;
        // int r = 0;
        // while(curr != end){
        //     node* nextNode = curr->next;
        //     removeBetween(curr);  // removeBetween already frees memory
        //     curr = nextNode;
        //     r++;
        // }

        start->prev->next = end->next;
        end->prev = start->prev;

        int r = size - (left + right);
        size =- r;
        return r;

    }

    void print(){
        node* temp = head;
        cout << "Size: " << size << endl;
        while(temp != nullptr){
            cout << temp->elem << " ";
            temp = temp->next;
        }

        cout << endl;
    }

};

int main(){
    List* list1 = new List();
    List* list2 = new List();
    List* curr = list1;

    char op;
    int num, pos;
    int left, right;

    do{
        cout << "Enter option: ";
        cin >> op;

        switch(op){
            case 'a':
                cin >> num;
                curr->addTail(num);
                break;
            case 'p':
                curr->print();
                break;
            case 's':
                curr = curr == list1? list2 : list1;
                break;
            case 'r':
                cin >> num;
                cout << "Position Removed: " << curr->remove(num) << endl;
                break;
            case '#':
                cin >> pos;
                cout << "Number removed: " << curr->removeAt(pos) << endl;
                break;
            case 'c':
                curr = (curr == list1)? list2 : list1;
                curr == list1? curr->combine(list2) : curr->combine(list1);
                break;
            case 'k':
                cin >> left;
                cin >> right;
                cout << "Numbers Removed: " << curr->corner(left, right) << endl;
                break;
            case '!':
                cin >> num;
                cout << "Numbers Removed: " << curr->retain(num) << endl;
                break;
        }

    }while(op != 'x');
}