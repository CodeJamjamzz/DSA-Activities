#include <iostream>
using namespace std;

struct node{
    int elem;
    int occurances;
    node* parent;
    node* left;
    node* right;
};

class BinarySearchTree {
    node* root;
    int size;

    public:
    BinarySearchTree(): root(nullptr), size(0){}

    node* createNode(int elem, node* parent){
        node* newnode = new node();
        newnode->elem = elem;
        newnode->parent = parent;
        newnode->occurances = 1;
        size++;
        return newnode;
    }

    node* insertmethod(int elem){
        if(!root){
            root = createNode(elem, nullptr); 
            return root;
        } 

        node* parent = insertsearch(elem, root);
        if(parent->elem == elem){
            parent->occurances++;
            return parent; 
        } 

        if(parent->elem < elem){
            parent->right = createNode(elem, parent); 
            return parent->right;
        } else if (parent->elem > elem){
            parent->left = createNode(elem, parent); 
            return parent->left;
        }

        return nullptr;
    }

    node* insertsearch(int elem, node* currentnode){
        if(!currentnode) throw logic_error("Currentnode is null");
        if(currentnode->elem == elem){
            return currentnode;
        }

        if(currentnode->elem < elem){
            if(!currentnode->right){
                return currentnode;
            } else {
                return insertsearch(elem, currentnode->right);
            }
        }

        if(currentnode->elem > elem){
            if(!currentnode->left){
                return currentnode;
            } else {
                return insertsearch(elem, currentnode->left);
            }
        }

        return nullptr;
    }

    int remove(int elem){
        node* removednode = removesearch(elem, root);
        if(!removednode){
            cout << "Element does not exist";
            return 0;
        } 

        int removed = removednode->elem;
        node* parent = removednode->parent;

        if(!removednode->left && !removednode->right){
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

        if(removednode->left && removednode->right){
            node* rightSubtree = removednode->right;
            node* mostLeft = leftmostNode(rightSubtree);

            node* parent = removednode->parent;

            if(mostLeft == rightSubtree){
                if(parent){
                    if(parent->right == removednode){
                        parent->right = mostLeft;
                    } else {
                        parent->left = mostLeft;
                    }
                } else {
                    root = mostLeft;
                }

                mostLeft->left = removednode->left;
                removednode->left->parent = mostLeft;
                removednode->parent = nullptr;
                delete removednode;
                size--;
                return removed;
            } else {
                if(parent){
                    if(parent->right == removednode){
                        parent->right = mostLeft;
                    } else {
                        parent->left = mostLeft;
                    }
                } else {
                    root = mostLeft;
                }

                mostLeft->parent->left = mostLeft->right; // Detach mostLeft from its old parent.
                if (mostLeft->right) {
                    mostLeft->right->parent = mostLeft->parent; // Update right child's parent if it exists.
                }
                mostLeft->parent = parent;

                mostLeft->left = removednode->left;
                mostLeft->right = removednode->right;

                removednode->left->parent = mostLeft;
                removednode->right->parent = mostLeft;

                removednode->parent = nullptr;
                delete removednode;
                size--;
                return removed;
            }
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
        } else {
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

        removednode->parent = nullptr;
        delete removednode;
        size--;
        return removed;
    }

    node* leftmostNode(node* currentnode){
        if(!currentnode->left) return currentnode;
        return leftmostNode(currentnode->left);
    }

    node* removesearch(int elem, node* currentnode){
        if(!currentnode) throw logic_error("Currentnode is null");
        if(currentnode->elem == elem){
            return currentnode;
        }

        if(currentnode->elem < elem){
            if(!currentnode->right){
                return nullptr;
            } else {
                return removesearch(elem, currentnode->right);
            }
        }

        if(currentnode->elem > elem){
            if(!currentnode->left){
                return nullptr;
            } else {
                return removesearch(elem, currentnode->left);
            }
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

        cout << currentnode->elem << " ";

        if(currentnode->right){
            myinordertraversal(currentnode->right);
        }
    }

    void mypreordertraversal(node* currentnode){
        cout << currentnode->elem << " ";
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

        cout << currentnode->elem << " ";
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

    bool searchboolean(int elem){
        return mysearch(elem, root);
    }

    bool mysearch(int elem, node* currentnode){
        if(currentnode->elem == elem) return true;
        if(!currentnode->right && !currentnode->left) return false;

        if(currentnode->elem < elem){
            return mysearch(elem, currentnode->right);
        } else if (currentnode->elem > elem){
            return mysearch(elem, currentnode->left);
        }

        return false;
    }

};

int main(){
    BinarySearchTree* tree = new BinarySearchTree();
    char option;
    int input;
    node* root = tree->insertmethod(47);

    do{
        cout << "Enter option: ";
        cin >> option;

        switch(option){
            case 'i':
                cout << "Enter number: ";
                cin >> input;
                tree->insertmethod(input);
                break;
            case 'r':
                cout << "Enter number to remove: ";
                cin >> input;
                cout << tree->remove(input) << endl;
                break;
            case 'p':
                tree->traversalprint();
                break;
        }
    } while(option != 'x');

}