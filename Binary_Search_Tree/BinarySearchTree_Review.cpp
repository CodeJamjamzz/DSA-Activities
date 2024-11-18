#include <iostream>
using namespace std;

struct node {
    int key;
    int value;
    node* parent;
    node* left;
    node* right;

    node(): key(0), value(0), parent(nullptr), left(nullptr), right(nullptr){} 
};

class BinarySearchTree {
    node* root;
    int size;

    public:
    BinarySearchTree(): root(nullptr), size(0){}

    node* createnode(int elem, int value, node* parent){
        node* newnode = new node();
        newnode->parent = parent;
        newnode->key = elem;
        newnode->value = value;
        size++;
        return newnode;
    }

    node* insertsearch(int elem, int value){
        return myinsertsearch(elem, value, root);
    }

    node* myinsertsearch(int elem, int value, node* currentnode){
        if(!currentnode) return nullptr;
        if(currentnode->key == elem){
            currentnode->value = value;
            return currentnode;
        }

        if(currentnode->key < elem){
            if(!currentnode->right){
                return currentnode;
            } else {
                return myinsertsearch(elem, value, currentnode->right);
            }
        } else {
            if(!currentnode->left){
                return currentnode;
            } else {
                return myinsertsearch(elem, value, currentnode->left);
            } 
        }
    }

    node* insert(int elem, int value){
        node* parent = insertsearch(elem, value);
        if(!parent){
            root = createnode(elem, value, nullptr);
            return root;
        }

        if(parent->key == elem){
            return parent;
        }

        node* newnode;
        if(parent->key < elem){
            parent->right = createnode(elem, value, nullptr);
            newnode = parent->right;
        } else {
            parent->left = createnode(elem, value, nullptr);
            newnode = parent->left;
        }

        return nullptr;
    }

    node* search(int elem, node* currentnode){
        if(!currentnode) return nullptr;
        if(currentnode->key == elem) return currentnode;

        if(currentnode->key < elem){
            return search(elem, currentnode->right);
        } else {
            return search(elem, currentnode->left);
        }
    
        return nullptr;
    }


    void inordertreversal(){
        myinordertraversal(root);
    }

    void preordertreversal(){
        mypreordertraversal(root);
    }

    void postordertreversal(){
        mypostordertraversal(root);
    }

    void myinordertraversal(node* currentnode){
        if(currentnode->left){
            myinordertraversal(currentnode->left);
        }

        cout << currentnode->key << "," << currentnode->value << " ";
        if(currentnode->right){
            myinordertraversal(currentnode->right);
        }
    }

    void mypreordertraversal(node* currentnode){
        cout << currentnode->key << "," << currentnode->value << " ";
        if(currentnode->left){
            mypreordertraversal(currentnode->left);
        }
        if(currentnode->right){
            mypreordertraversal(currentnode->right);
        }
    }

    void mypostordertraversal(node* currentnode){
        
        if(currentnode->left){
            mypostordertraversal(currentnode->left);
        }
        if(currentnode->right){
            mypostordertraversal(currentnode->right);
        }

        cout << currentnode->key << "," << currentnode->value << " ";
    }

    void traversalprint(){
        cout << "\nPreorder Traversal: ";
        preordertreversal();

        cout << "\nInorder Traversal: ";
        inordertreversal();

        cout << "\nPostorder Traversal: ";
        postordertreversal();

        cout << endl;
    }

    node* mostLeft(node* currentnode){
        while(currentnode && currentnode->left){
            currentnode = currentnode->left;
        }
        return currentnode;
    }

    int remove(int elem){
        node* removednode = search(elem, root);
        if(!removednode) return -1;
        int removed = removednode->key;

        node* parent = removednode->parent;
        if(!removednode->right && !removednode->left){
            if(parent){
                if(parent->right == removednode){
                    parent->right = nullptr;
                } else {
                    parent->left = nullptr;
                }
            } else {
                root = nullptr;
            }

            removednode->parent = nullptr;
            delete removednode;
            size--;
            return removed;
        }

        if(removednode->right && removednode->left){
            node* mostleft = mostLeft(removednode->right);
            node* rightSubtree = removednode->right;

            if(mostleft == rightSubtree){
                if(parent){
                    if(parent->right == removednode){
                        parent->right = rightSubtree;
                    } else {
                        parent->left = rightSubtree;
                    }

                } else {
                    root = rightSubtree;
                }

                mostleft->left = removednode->left;
                removednode->left->parent = mostleft;
                removednode->parent = nullptr;
                delete removednode;
                size--;
                return removed;

            } else {
                if(parent){
                    if(parent->right == removednode){
                        parent->right = mostleft;
                    } else {
                        parent->left = mostleft;
                    }
                } else {
                    root = mostleft;
                }

                mostleft->parent->left = mostleft->right;
                if(mostleft->right){
                    mostleft->parent->left = mostleft->right;
                }

                mostleft->parent = parent;

                mostleft->left = removednode->left;
                mostleft->right = removednode->right;

                removednode->left->parent = mostleft;
                removednode->right->parent = mostleft;

                removednode->parent = nullptr;
                delete removednode;
                size--;
                return removed;
            }

        }

        if(!removednode->right){
            if(parent){
                if(parent->right == removednode){
                    parent->right = removednode->left;
                } else {
                    parent->left = removednode->left;
                }
            } else {
                root = removednode->left;
            }

            removednode->left->parent = parent;
        }

        if(!removednode->left){
            if(parent){
                if(parent->right == removednode){
                    parent->right = removednode->right;
                } else {
                    parent->left = removednode->right;
                }
            } else {
                root = removednode->right;
            }

            removednode->right->parent = parent;
        }

        removednode->parent = nullptr;
        delete removednode;
        size--;
        return removed;

    }

};

int main(){
    BinarySearchTree* tree = new BinarySearchTree();
    char option;
    int input, value;
    node* root = tree->insert(50, 1);

    do{
        cout << "Enter option: ";
        cin >> option;

        switch(option){
            case 'i':
                cout << "Enter number: ";
                cin >> input;

                cout << "Enter the value of the key: ";
                cin >> value;
                tree->insert(input, value);
                break;
            case 's':
                cout << "Enter number to search: ";
                cin >> input;
                (tree->search(input, root))? cout << "Number is present\n" : cout << "Number is not present\n";
                break;
            case 'p':
                tree->traversalprint();
                break;
            case 'r':
                cout << "Enter number to remove: ";
                cin >> input;
                cout << tree->remove(input) << "\n";
                break;
        }
    } while(option != 'x');

}
