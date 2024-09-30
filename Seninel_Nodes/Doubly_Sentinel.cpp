    #include <iostream>
    using namespace std;

    struct node{
        int elem;
        node* next;
        node* prev;
    };

    class List{
        node* head;
        int size;

        public:
        List(){
            head = (node*) calloc(1,sizeof(node));
            head->elem = 0;
            head->next = head;
            head->prev = head;
            size = 0;
        }

        void addHead(int num){
            node* newnode = (node*) calloc(1,sizeof(node));
            newnode->elem = num;

            newnode->next = head->next;
            newnode->prev = head;
            head->next->prev = newnode;
            head->next = newnode;
            size++;
        }

        void addTail(int num){
            node* newnode = (node*) calloc(1,sizeof(node));
            newnode->elem = num;

            newnode->prev = head->prev;
            newnode->next = head;
            head->prev->next = newnode;
            head->prev = newnode;
            size++;
        }

        void removeLast(){
            node* last = head->prev;

            last->prev->next = head;
            head->prev = last->prev;

            free(last);
            size--;
        }

        void print(){
            node* temp = head->next;
            while(temp != head){
                cout << temp->elem << " ";
                temp = temp->next;
            }

            cout << endl;
        }
    };

    int main(){
        List* list = new List();
        char op;
        int num, pos;

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
                case 'l':
                    list->removeLast();
                    break;
                case 'p':
                    list->print();
                    break;
            }

        } while(op != 'x');
    }