#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node{
    int elem;
    node* parent;
    node* left;
    node* right;
};

class BinaryTree {
    node* root;
    int size;

    public:
    BinaryTree(): root(nullptr), size(0){}

    node* addRoot(int num){
        if(root) throw logic_error("There is already a root");

        root = new node();
        root->elem = num;
        size++;
        return root;
    }

    node* addLeft(node* currentnode, int num){
        if(currentnode->left) throw logic_error("There is already a left child");

        currentnode->left = new node();
        currentnode->left->elem = num;
        currentnode->left->parent = currentnode;
        size++;
        return currentnode->left;
    }

    node* addRight(node* currentnode, int num){
        if(currentnode->right) throw logic_error("There is already a right child");

        currentnode->right = new node();
        currentnode->right->elem = num;
        currentnode->right->parent = currentnode;
        size++;
        return currentnode->right;
    }

    void Inorder_traveral(node* currentnode){
        if(currentnode->left){
            Inorder_traveral(currentnode->left);
        }

        cout << currentnode->elem << " ";

        if(currentnode->right){
            Inorder_traveral(currentnode->right);
        }
    }

    void Preorder_traversal(node* currentnode){
        cout << currentnode->elem << " ";
        if(currentnode->left){
            Preorder_traversal(currentnode->left);
        }

        if(currentnode->right){
            Preorder_traversal(currentnode->right);
        }
    }

    void Postorder_traversal(node* currentnode){
        if(currentnode->left){
            Postorder_traversal(currentnode->left);
        }

        if(currentnode->right){
            Postorder_traversal(currentnode->right);
        }

        cout << currentnode->elem << " ";
    }

    void Breadth_FirstSearch_Traversal(node* curretnode){
        queue<node*> tree;

        tree.push(curretnode);

        while(!tree.empty()){
            node* current = tree.front();
            tree.pop();

            cout << current->elem << " ";

            if(current->left){
                tree.push(current->left);
            }

            if(current->right){
                tree.push(current->right);
            }
        }
    }

};

int main(){
    BinaryTree* tree = new BinaryTree();

    node* root = tree->addRoot(13);

    node* ten = tree->addLeft(root, 10);
    node* eleven = tree->addRight(root, 11);

    node* four = tree->addLeft(ten, 4);
    node* five = tree->addRight(ten, 5);

    node* twelve = tree->addLeft(eleven, 12);
    node* fifteen = tree->addRight(eleven, 15);

    tree->Inorder_traveral(root); cout << endl;
    tree->Preorder_traversal(root);cout << endl;
    tree->Postorder_traversal(root);cout << endl;

    tree->Breadth_FirstSearch_Traversal(root); cout << endl;
}