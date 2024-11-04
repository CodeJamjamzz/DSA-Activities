#include <iostream>
#include <bits/stdc++.h>
#include <stdexcept>
using namespace std;

struct node{
    int elem;
    node* left;
    node* right;
    node* parent;

    int depth(){
        if(!parent) return 0;
        return 1 + parent->depth();
    }

    int height(){
        if(!left && !right) return 0;
        int leftheight = 0, rightheight = 0;

        if(left){
            leftheight = left->height();
        }

        if(right){
            rightheight = right->height();
        }

        return 1 + max(leftheight, rightheight);
    }
};

class BinaryTree{
    node* root;
    int size;

    public:
    BinaryTree(): size(0), root(nullptr) {}

    public:
    node* addRoot(int elem){
        if(root) throw logic_error("There is already a root");

        root = new node();
        root->elem = elem;
        size++;
        return root;
    }

    node* addLeft(node* currentnode, int elem){
        if(currentnode->left) throw logic_error("There is aleady a left child");

        currentnode->left = new node();
        currentnode->left->elem = elem;
        currentnode->left->parent = currentnode;
        size++;
        return currentnode->left;
    }

    node* addRight(node* currentnode, int elem){
        if(currentnode->right) throw logic_error("There is aleady a right child");

        currentnode->right = new node();
        currentnode->right->elem = elem;
        currentnode->right->parent = currentnode;
        size++;
        return currentnode->right;
    }

    void print_preorder(node* currentnode){
        cout << currentnode->elem << " ";
        if(currentnode->left){
            print_preorder(currentnode->left);
        }
        if(currentnode->right){
            print_preorder(currentnode->right);
        }
    }
};

int main(){
    BinaryTree* tree = new BinaryTree();

    node* root = tree->addRoot(4);
    node* five = tree->addRight(root, 5);
    node* six = tree->addLeft(root, 6);

    cout << six->height() << endl;
    tree->print_preorder(root);
}