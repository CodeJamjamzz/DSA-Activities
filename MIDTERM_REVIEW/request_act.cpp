#include <iostream>
using namespace std;

struct Person{
    string firstname;
    string lastname;
    int age;
    int req[4];

    string getname(){
        return firstname + " " + lastname;
    }

    void printreq(){
        for(int i = 0; i < 4; i++){
            if(req[i] == 1){
                if(i == 0){
                    cout << "M ";
                } else if (i == 1){
                    cout << "A ";
                } else if (i == 2){
                    cout << "C ";
                } else {
                    cout << "D ";
                }
            }
        }
        cout << endl;
    }
};

struct node{
    Person* person;
    node* next;
    node* prev;
};

class List{
    node* head;
    node* tail;
    int size;
    node* senior;

    public:
    List(){
        head = (node*) calloc(1,sizeof(node));
        tail = (node*) calloc(1,sizeof(node));
        tail->prev = head;
        head->next = tail;
        head->prev = nullptr;
        tail->next = nullptr;
        senior = head;
        size = 0;
    }

    node* addbetween(Person* p, node* pred, node* succ){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->person = p;

        newnode->prev = pred;
        newnode->next = succ;
        succ->prev = newnode;
        pred->next = newnode;
        size++;
        return newnode;
    }

    void add(Person* p){
        if(p->age >= 60){
            senior = addbetween(p, senior, senior->next);
        } else {
            addbetween(p, tail->prev, tail);
        }
    }

    void remove(node* n){
        node* pred = n->prev;
        node* succ = n->next;

        pred->next = succ;
        succ->prev = pred;
        free(n);
        return; 
    }

    Person* fastlane(){
        node* temp = head->next;
        Person* ret = nullptr;

        int ctr = 0;
        while(temp != tail){
            
            ctr = 0;
            for(int i = 0; i < 4; i++){
                if(temp->person->req[i] == 1){
                    ctr++;
                }
            }
            
            if (ctr == 1){
                ret = temp->person;
                remove(temp);
                return ret;
            }

            temp = temp->next;
        }

        return nullptr;
    }


    node* serveRequest(char ch){
        int index;
        switch(ch){
            case 'M':
                index = 0;
                break;
            case 'A':
                index = 1;
                break;
            case 'C':
                index = 2;
                break;
            case 'D':
                index = 3;
                break;
        }

        node* temp = head->next;
        while(temp != tail){
            if(temp->person->req[index] == 1){
                temp->person->req[index] = 0;

                int ctr = 0;
                for(int i = 0; i < 4; i++){
                    if(temp->person->req[i] == 1){
                        ctr++;
                    }
                }

                if(ctr == 0){
                    node* ret = temp;
                    remove(temp);
                    return ret;
                } else {
                    return temp;
                }
            }

            temp = temp->next;
        }

        return nullptr;
    }

    void delay(string name, int back){
        node* temp = head->next;
        while(temp != tail){
            if(temp->person->firstname == name || temp->person->lastname == name){
                break;
            }

            temp = temp->next;
        }

        node* n = temp;
        node* pred = n->prev;
        node* succ = n->next;
        pred->next = succ;
        succ->prev = pred;

        for(int i = 0; i < back; i++){
            if(pred == tail) break;
            pred = pred->next;
        }

        succ = pred->next;
        n->prev = pred;
        n->next = succ;
        pred->next = n;
        succ->prev = n;
        
        return;
    }

    void advance(string name, int forward){
        node* temp = head->next;
        while(temp != tail){
            if(temp->person->firstname == name || temp->person->lastname == name){
                break;
            }
            temp = temp->next;
        }

        node* n = temp;
        node* pred = n->prev;
        node* succ = n->next;
        pred->next = succ;
        succ->prev = pred;

        for(int i = 0; i < forward; i++){
            if(succ== head->next) break;
            succ = succ->prev;
        }

        pred = succ->prev;
        n->next = succ;
        n->prev = pred;
        pred->next = n;
        succ->prev = n;
        return;

    }

    void swap(node* node1, node* node2){
        node* Node1Prev = node1->prev;
        node* Node1Next = node1->next;
        node* Node2Prev = node2->prev;
        node* Node2Next = node2->next;

        if(Node1Next == node2){
            Node2Next->prev = node1;
            node1->next = Node2Next;

            Node1Prev->next = node2;
            node2->prev = Node1Prev;

            node2->next = node1;
            node1->prev = node2;

        } else if (Node2Next == node1){
            Node1Next->prev = node2;
            node2->next = Node1Next;

            Node2Prev->next = node1;
            node1->prev = Node2Prev;

            node1->next = node2;
            node2->prev = node1;
        } else {
            Node1Next->prev = node2;
            Node1Prev->next = node2;

            Node2Next->prev = node1;
            Node2Prev->next = node1;

            node1->prev = Node2Prev;
            node1->next = Node2Next;

            node2->next = Node1Next;
            node2->prev = Node1Prev;
        }

        return;
    }

    node* find(string name){
        node* temp = head->next;
        while(temp != tail){
            if(temp->person->firstname == name || temp->person->lastname == name){
                break;
            }
            temp = temp->next;
        }

        return temp;
    }

    void trade(string node1, string node2){

        node* firstnode = find(node1);
        node* secondnode = find(node2);
        swap(firstnode, secondnode);
    }

    void addHead(Person* p){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->person = p;

        newnode->next = head->next;
        head->next->prev = newnode;

        head->next = newnode;
        newnode->prev = head;
        size++;
        return;
    }

    void addTail(Person* p){
        node* newnode = (node*) calloc(1,sizeof(node));
        newnode->person = p;

        newnode->next = tail;

        tail->prev->next = newnode;
        newnode->prev = tail->prev;

        tail->prev = newnode;
        size++;
        return;
    }

    void print(){
        int ctr = 1;
        cout << "Head to Last: " << endl;
        node* temp = head->next;
        while(temp != tail){
            cout << ctr << ". " << temp->person->getname() << " (" << temp->person->age << ") - req: ";
            temp->person->printreq();

            ctr++;
            temp = temp->next; 
        }

        cout << "Last to Head: " << endl;
        node* temp2 = tail->prev;
        while(temp2 != head){
            ctr--;
            cout << ctr << ". "<< temp2->person->getname() << " (" << temp2->person->age << ") - req: ";
            temp2->person->printreq();

            temp2 = temp2->prev; 
        }
        return;
    }
};

int main(){
    List* list = new List();
    Person* p;
    node* serve;
    Person *per;
    char op, ch;
    string name, name2;
    int num;

    do{
        cout << "Enter options: ";
        cin >> op;

        switch(op){
            case 'a':
                p = new Person();
                cout << "Enter name: ";
                cin >> p->firstname;
                cin >> p->lastname;

                cout << "Enter age: ";
                cin >> p->age;

                cout << "Requests: ";
                for(int i = 0; i < 4; i++){
                    cin >> p->req[i];
                }

                list->add(p);
                break;
            case 'h':
                p = new Person();
                cout << "Enter name: ";
                cin >> p->firstname;
                cin >> p->lastname;

                cout << "Enter age: ";
                cin >> p->age;

                cout << "Requests: ";
                for(int i = 0; i < 4; i++){
                    cin >> p->req[i];
                }

                list->addHead(p);
                break;
            case 't':
                p = new Person();
                cout << "Enter name: ";
                cin >> p->firstname;
                cin >> p->lastname;

                cout << "Enter age: ";
                cin >> p->age;

                cout << "Requests: ";
                for(int i = 0; i < 4; i++){
                    cin >> p->req[i];
                }

                list->addTail(p);
                break;
            case 's':
                cin >> ch;
                serve = list->serveRequest(ch);
                cout << "You just got served: " << serve->person->getname() << endl;
                break;
            case 'f':
                per = list->fastlane(); 
                if(per == nullptr){
                    cout << "Nothing" << endl;
                } else {
                    cout << "Thank you! " << per->getname() << endl;
                }
                break;
            case 'd':
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter num: ";
                cin >> num;

                list->delay(name, num);
                break;
            case '+':
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter num: ";
                cin >> num;

                list->advance(name, num);
                break;
            case '-':  
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter name: ";
                cin >> name2;

                list->trade(name, name2);
                break;
            case 'p':
                list->print();
                break;
        }

    }while(op != 'x');
}