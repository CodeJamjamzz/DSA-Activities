#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node{
    int elem;
    node* left;
    node* right;
    node* parent;

    public:
    node(int num): elem(num), left(nullptr), right(nullptr), parent(nullptr){}   
    node(): elem(0), left(nullptr), right(nullptr), parent(nullptr){}
};

class BinaryTree {
    node* root;
    int size;

    public:
    BinaryTree(): root(nullptr), size(0){}

    node* addRoot(int element) noexcept(false) {
        if(root) throw  runtime_error("Root already has a value");

        root = new node();
        root->elem = element;
        size++;
        return root;
    }

    node* addLeft(node* currentnode, int num) noexcept(false) {
        if(currentnode->left) throw runtime_error("There is already a left child");

        currentnode->left = new node();
        currentnode->left->elem = num;
        currentnode->left->parent = currentnode;
        size++;
        return currentnode->left;
    }

    node* addRight(node* currentnode, int num){
        if(currentnode->right) throw runtime_error("There is already a right child");

        currentnode->right = new node();
        currentnode->right->elem = num;
        currentnode->right->parent = currentnode;
        size++;
        return currentnode->right;
    }

    int set(node* currentnode, int elem){
        if(!currentnode) throw runtime_error("The curretnode is empty");

        int removedelem = currentnode->elem;
        currentnode->elem = elem;
        return removedelem;
    }

    int remove(node* currentnode){
        if(!currentnode) throw runtime_error("The curretnode is empty");
        if(currentnode->left && currentnode->right) throw runtime_error("The current node has two children");

        node* child;
        if(!currentnode->left && !currentnode->right){
            child = nullptr;
        } else {
            child = (currentnode->left)? currentnode->left : currentnode->right;
        }
        
        if(currentnode->parent){
            if(child){
                child->parent = currentnode->parent;
            }

            (currentnode->parent->left == currentnode)? currentnode->parent->left = child : currentnode->parent->right = child;
        } else {
            root = currentnode;
        }
        
        int removedElem = currentnode->elem;
        delete currentnode;
        size--;
        return removedElem;
    }

    node* removeRoot(node* currentnode){
        if(!currentnode) throw runtime_error("The curretnode is empty");
        if(currentnode->left && currentnode->right) throw runtime_error("The current node has two children");

        node* child;
        if(!currentnode->left && !currentnode->right){
            child = nullptr;
        } else {
            child = (currentnode->left)? currentnode->left : currentnode->right;
        }
        
        if(currentnode->parent){
            if(child){
                child->parent = currentnode->parent;
            }

            (currentnode->parent->left == currentnode)? currentnode->parent->left = child : currentnode->parent->right = child;
        } else {
            root = child;
            child->parent = nullptr;
        }

        delete currentnode;
        size--;
        return root;
    }

    node* getRoot(){
        return root;
    }

    void setRoot(node* newnode){
        root = newnode;
        return;
    }

    int _size(){
        return size;
    }

    bool isLeaf(node* currentnode){
        if(currentnode->left && currentnode->right){
            return false;
        }

        return true;
    }

    void attach(node* currentnode, BinaryTree* tree1, BinaryTree* tree2){
        if(!currentnode || !isLeaf(currentnode)) throw new runtime_error("node is either empty or is not a leaf");

        currentnode->left = tree1->getRoot();
        currentnode->right = tree2->getRoot();

        tree1->getRoot()->parent = currentnode;
        tree2->getRoot()->parent = currentnode;

        size += tree1->_size();
        size += tree2->_size();

        tree1->setRoot(nullptr);
        tree2->setRoot(nullptr);

        return;
    }

    void insert(node* currentnode, int value){
        if(!currentnode){
            root = new node();
            root->elem = value;
            size++;
            return;
        }

        queue<node*> current;
        current.push(currentnode);

        while(!current.empty()){

            node* curr = current.front();
            current.pop();

            if(curr->left){
                current.push(curr->left);
            } else {
                curr->left = new node();
                curr->left->elem = value;
                size++;
                return;
            }

            if(curr->right){
                current.push(curr->right);
            } else {
                curr->right = new node();
                curr->right->elem = value;
                size++;
                return;
            }

            
        }
    }

    int depth(node* currentnode, int target, int depthnumber){
        if(currentnode == nullptr){
            return -1;
        }

        if(currentnode->elem == target){
            return depthnumber;
        }

        int left = depth(currentnode->left, target, depthnumber + 1);
        if(left != -1){
            return left;
        }

        return depth(currentnode->right, target, depthnumber + 1);
    }

    int finddepth(node* currentnode){
        if(currentnode == nullptr){
            return -1;
        }

        int left = finddepth(currentnode->left);
        int right = finddepth(currentnode->right);
        return max(left, right) + 1; 
    }

    bool search(node* currentnode, int value){
        if(!currentnode) return false;
        if(currentnode->elem == value) return true;
        return search(currentnode->left, value) || search(currentnode->right, value); 
    }

    void preorder_print(node* currentnode){
        cout << currentnode->elem << " ";

        if(currentnode->left){
            preorder_print(currentnode->left);
        }

        if(currentnode->right){
            preorder_print(currentnode->right);
        }
    }
};

int main(){
    node* root;
    BinaryTree* tree = new BinaryTree();

    //First Test Case
    root = tree->addRoot(7);
    // node* twenty = tree->addLeft(root, 20);
    // node* twentytwo = tree->addRight(root, 22);

    // node* twentyfive = tree->addLeft(twenty, 25);
    // node* fifteen = tree->addRight(twenty, 15);

    // node* ten = tree->addLeft(twentytwo, 10);

    // cout << "First: " << endl; 
    // tree->preorder_print(root);
    // cout << endl;

    // cout << "Removed : " << tree->remove(twentytwo) << endl;
    // cout << "Current: " << endl; 
    // tree->preorder_print(root);

    // cout << "Removed : " << tree->remove(ten) << endl;
    // cout << "Current: " << endl; 
    // tree->preorder_print(root);

    // root = tree->removeRoot(root);
    // cout << "Root : " << root->elem << endl;
    // cout << "Current: " << endl; 
    // tree->preorder_print(root);

    BinaryTree* tree1 = new BinaryTree();

    node* tree1_root = tree1->addRoot(6);
    node* five = tree1->addLeft(tree1_root, 5); 

    BinaryTree* tree2 = new BinaryTree();
    node* tree2_root = tree2->addRoot(8);
    node* nine = tree2->addLeft(tree2_root, 9);
    node* ten = tree2->addRight(tree2_root, 10);

    tree->attach(root, tree1, tree2);
    tree->preorder_print(root);
    cout << endl;

    int num = 9;
    // cout << "Number to Search: ";
    // cin >> num;
    (tree->search(root, num))? cout << num << " is Present" << endl : cout << num << " is not Present" << endl;
    // cout << "Number to Search: ";
    // cin >> num;
    (tree->search(root, num))? cout << num << " is Present" << endl : cout << num << " is not Present" << endl;

    tree->insert(root, 9);
    tree->preorder_print(root);

    cout << "\nDepth: " << tree->depth(root,7,0);
    cout << "\nDepth: " << tree->finddepth(root);
    return 0;
}