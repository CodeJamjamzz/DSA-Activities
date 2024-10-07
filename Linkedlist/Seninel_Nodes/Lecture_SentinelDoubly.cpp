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

        void addbetween(int num, node* pred, node* succ){
            node* newnode = (node*) calloc(1,sizeof(node));
            newnode->elem = num;

            succ->prev = newnode;
            pred->next = newnode;

            newnode->prev = pred;
            newnode->next = succ;
            size++;
            return;
        }

        ~List(){
            cout << "deleting myself" << endl;
            node* curr = head->next;
            while(curr != nullptr){
                free(curr->prev);
                curr = curr->next;
            }
        }

        public:
        List(){
            head = (node*) calloc(1,sizeof(node));
            tail = (node*) calloc(1,sizeof(node));
            head->next = tail;
            tail->prev = head;

            head->prev = nullptr;
            tail->next = nullptr;
            size = 0;
        }

        void addHead(int num){
            addbetween(num, head, head->next);
        }

        void addTail(int num){
            addbetween(num, tail->prev, tail);
        }

        int remove(node* n){
            node* pred = n->prev;
            node* succ = n->next;

            int ret = n->elem;
            pred->next = succ;
            succ->prev = pred;
            free(n);
            size--;
            return ret;
        }

        int removeHead(){
            return remove(head->next);
        }

        int removeTail(){
            return remove(tail->next);
        }

        int remove_node(int num){
            node* curr = head->next;
            int pos = 1;
            while(curr != tail){
                if(curr->elem  == num){
                    remove(curr);
                    return pos;
                }
                pos++;
                curr = curr->next;
            }
        }

        void print(){
            node* temp = head->next;
            while(temp != tail){
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
                    cin >> num;
                    cout << "Removed At: " << list->remove_node(num);
                    break;
                case 'p':
                    list->print();
                    break;
            }

        } while(op != 'x');

        return 0;
    }