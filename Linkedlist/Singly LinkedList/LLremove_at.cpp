#include <iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *next;
    
    Node(int num): data(num) , next(nullptr){}
};

class List{
    Node* head;
    public:
    
    List(): head(nullptr){}
    
    void add(int num){
        Node* temp = head;
        
        Node* newnode = new Node(num);
        
        if(head == nullptr){
            head = newnode;
        } else {
            while(temp->next != nullptr){
                temp = temp->next;
            }
            
            temp->next = newnode;
        }
    }
    
    void print(){
        Node* temp = head;
        while(temp != nullptr){
            cout << temp->data << " ";
            temp = temp->next;
        }
        
        cout << endl;
    }
    
    bool remove_num(int pos){
        Node *temp = head;
        
        if(pos == 1){
            Node* rem = head;
            head = temp->next;
            delete rem;
            return true;
        }
        
        int ctr = 1;
        while(temp != nullptr && ctr < pos - 1){
            // if(ctr == pos - 1){
            //     break;
            // }
            
            temp = temp->next;
            ctr++;
        }
        
        if(temp->next == nullptr || ctr != pos - 1){
            return false;
        }
        
        Node* rem = temp->next;
        temp->next = temp->next->next;
         
        delete rem;
        return true;
    }
};

int main(){
    List* list = new List();
    
    int size;
    cout << "Enter size of linked list: ";
    cin >> size;
    
    int num;
    for(int i = 0; i < size; i++){
        cout << "Enter element " << i + 1 << ": ";
        cin >> num;
        list->add(num);
    }
    
    cout << "Original list: ";
    list->print();
    
    int rem;
    cout << "Enter position of data to be removed: ";
    cin >> rem;
    
    if(list->remove_num(rem)){
        cout << "Updated list: ";
        list->print();
    } else {
        cout << "Invalid position" << endl;
        cout << "Updated list: ";
        list->print();
    }

}