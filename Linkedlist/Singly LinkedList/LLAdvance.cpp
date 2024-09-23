#include <iostream>
using namespace std;

class Node{
    int data;
    Node *next;

    public:
    Node(): data(0), next(nullptr){}

    Node(int num): data(num) , next(nullptr){}
    Node(int num, Node* node): data(num) , next(node){}

    int getNode(){
        return data;
    }

    Node* getnext(){
        return next;
    }

    void setnext(Node* node){
        this->next = node;
    }

};

class List{
    Node* head;

    public:
    List(): head(nullptr){}

    void addAtbeggining(int num){
        Node* temp = head;

        Node* newNode = new Node(num, head);
        head = newNode;
    }

    void print(){
        Node* temp = head;
        cout << "Linked List: ";
        while(temp != nullptr){
            cout << temp->getNode() << " ";
            temp = temp->getnext();
        }
        cout << endl;
    }
};

int main(){
    List* list = new List();

    char op;

    do{
        cout << "Enter Option: ";
        cin >> op;

        switch(op){
            case 'a':
                int num;
                cout << "Enter num: ";
                cin >> num;

                list->addAtbeggining(num);
                break;
            case 'p':
                list->print();
                break;
        }

    }while(op != 'x');
}