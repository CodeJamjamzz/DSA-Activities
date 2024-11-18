#include <iostream>
#include <string>
using namespace std;

struct node {
    int elem;
    node* parent;
    node* left;
    node* right;
};

// not yet done 
class BinarySearchTree {
    public:
    node* root;
    int size;

    BinarySearchTree(): root(nullptr), size(0){}

    node* createNode(int elem , node* parent){
        node* newnode = new node();
        newnode->elem = elem;
        newnode->parent = parent;
        size++;
        return newnode;
    }

    bool Search(int elem){
        return mySearch(elem, root);
    }

    bool mySearch(int elem, node* currentnode){
        if(!currentnode) return false;
        if(currentnode->elem == elem) return true;

        if(currentnode->elem < elem) return mySearch(elem, currentnode->right);
        if(currentnode->elem > elem) return mySearch(elem, currentnode->left);
        return false;
    }

    void preorder_traversal(){
        mypreorder_traversal(root);
    }

    void mypreorder_traversal(node* currentnode){
        cout << currentnode->elem << " ";

        if(currentnode->left) mypreorder_traversal(currentnode->left);
        if(currentnode->right) mypreorder_traversal(currentnode->right);
    }
};

node* opInput(BinarySearchTree* tree, string prompt, node* parent, bool check){

    int elem;
    cout << "Enter " << prompt << " ";
    cin >> elem;

    if(!check){
        return tree->createNode(elem, parent);
    }

    node* current = tree->createNode(elem, parent);
    current->left = opInput(tree, "the left child: ", current, false);
    current->right = opInput(tree, "the right child: ", current, false);
    return current;
}

int main(){
    BinarySearchTree* tree = new BinarySearchTree();

    char op;
    int search;

    tree->root = opInput(tree, "root:", nullptr, true);
    node* depth1_right = opInput(tree, "the right: " , tree->root, true);
    depth1_right->parent = tree->root->right;
    tree->root->right->left = depth1_right;
    node* depth1_left = opInput(tree, "the left: " , tree->root, true);
    depth1_left->parent = tree->root->left;
    tree->root->left->right = depth1_left;

    do {

        cout << "Enter option: ";
        cin >> op;

        switch(op){
            case 's':
                cout << "Enter number to search: ";
                cin >> search;

                (tree->Search(search))? cout << "True" : cout << "False";
                cout << endl;

                break;
            case 'p':
                tree->preorder_traversal();
                cout << endl;
                break;
        }
    } while (op != 'x');
}