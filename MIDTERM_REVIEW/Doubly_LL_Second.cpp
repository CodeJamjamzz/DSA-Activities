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
    int size = 0;

    public:
    List(): head(nullptr), tail(nullptr), size(0){}

    int add(int num){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->elem = num;

        if(!head){
            head = newnode;
            tail = newnode;
            size++;
            return 1;
        }

        node* headctr = head;
        int headnum = 0;

        node* tailctr = tail;
        int tailnum = 0;

        while(headctr && headctr->elem < num){
            headnum++;
            headctr = headctr->next;
        }

        while(tailctr != nullptr && tailctr->elem > num){
            tailnum++;
            tailctr = tailctr->prev;
        }


        if(headnum <= tailnum){                 // 1,2,3,4,9   //1,2,7,8,9
            addbetween(newnode, headctr->prev, headctr);
            return 1;
        } else {
            addbetween(newnode, tailctr, tailctr->next);
            return 2;
        }

    }

    void addbetween(node* n, node* pred, node* succ){

        if(pred){
           pred->next = n; 
        } else {
            head = n;
        }
        
        if(succ){
           succ->prev = n; 
        } else {
            tail = n;
        }

        n->prev = pred;
        n->next = succ;
        
    }

    void print(){
        node* temp = head;
        while(temp){
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
                cout << "Start: "; 
                
                if(1 == list->add(num)){
                    cout << "Head";
                } else { 
                    cout << "Tail";
                }

                cout << endl;

                break;
            case 'p':
                list->print();
                break;
        }
        
        
    }while(op != 'x');
}

        // if(!prev){
        //     n->next = succ;
        //     n->prev = prev;
        //     succ->prev = n;
        //     head = n;
        //     size++;
        //     return;
        // } else if (!succ){
        //     prev->next = n;
        //     n->prev = prev;

        //     n->next = succ;
        //     tail = n;
        //     size++;
        //     return;
        // }

        // prev->next = n;
        // succ->prev = n;

        // n->next = succ;
        // n->prev = prev;
        // size++;
        // return;