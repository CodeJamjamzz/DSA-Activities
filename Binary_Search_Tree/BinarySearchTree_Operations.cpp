#include <iostream>
#include <exception>
using namespace std;

struct node{
    int elem;
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
        size++;
        return newnode;
    }

    node* insertmethod(int elem){
        if(!root){
            root = createNode(elem, nullptr); 
            return root;
        } 

        node* parent = search(elem, root);
        if(parent->elem == elem) return parent; 

        if(parent->elem < elem){
            parent->right = createNode(elem, parent); 
            return parent->right;
        } else if (parent->elem > elem){
            parent->left = createNode(elem, parent); 
            return parent->left;
        }

        return nullptr;
    }

    node* search(int elem, node* currentnode){
        if(!currentnode) throw logic_error("Currentnode is null");

        if(currentnode->elem == elem) return currentnode;

        if(currentnode->elem < elem){
            if(!currentnode->right){
                return currentnode;
            } else {
                return search(elem, currentnode->right);
            }
        }

        if(currentnode->elem > elem){
            if(!currentnode->left){
                return currentnode;
            } else {
                return search(elem, currentnode->left);
            }
        }
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
    node* root = tree->insertmethod(50);

    do{
        cout << "Enter option: ";
        cin >> option;

        switch(option){
            case 'i':
                cout << "Enter number: ";
                cin >> input;
                tree->insertmethod(input);
                break;
            case 's':
                cout << "Enter number to search: ";
                cin >> input;
                (tree->searchboolean(input))? cout << "Number is present\n" : cout << "Number is not present\n";
                break;
            case 'p':
                tree->traversalprint();
                break;
        }
    } while(option != 'x');

}

    // node* insert(int elem){
    //     if(!root) root = createNode(elem, nullptr);
    //     return myinsertmethod(elem, root);
    // }

    // node* myinsertmethod(int elem, node* currentnode){
    //     if(!currentnode->right && !currentnode->left){
    //         if(currentnode->elem < elem){
    //             currentnode->right = createNode(elem, currentnode->right);
    //             return currentnode->right;
    //         } else {
    //             currentnode->left = createNode(elem, currentnode->left);
    //             return currentnode->left;
    //         }
    //     } 
        
    //     if (currentnode->elem > elem && !currentnode->left){
    //         currentnode->left = createNode(elem, currentnode->left);
    //         return currentnode->left;
    //     } else if (currentnode->elem < elem && !currentnode->right){
    //         currentnode->right = createNode(elem, currentnode->right);
    //         return currentnode->right;
    //     }

    //     if(currentnode->elem < elem){
    //         return myinsertmethod(elem, currentnode->right);
    //     } else {
    //         return myinsertmethod(elem, currentnode->left);
    //     }

    // }