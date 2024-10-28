#include <iostream>
using namespace std;

struct node{
    int elem;
    node* left;
    node* right;
    node* parent;

    public: 
    node(int num){
        elem = num;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
    }

    node(){
        elem = 0;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
    }

};

class BinaryTree{
    node* root;
    int size;

    public:
    BinaryTree(): root(nullptr), size(0){}

    node* addroot(int num){
        if(root != nullptr){
            throw runtime_error(to_string(num) + "cannot be a root" );
        }

        root = new node(num);
        size++;
        return root;
    }

    node* addleft(node* parent, int num){
        if(parent->left){
            throw new runtime_error(to_string(parent->elem) + "already has an left child");
        }

        parent->left = new node();
        parent->left->elem = num;
        parent->left->parent = parent;
        size++;
        return parent->left;
    }
    node* addright(node* parent, int num){
        if(parent->right){
            throw new runtime_error(to_string(parent->elem) + "already has a right child");
        }

        parent->right = new node();
        parent->right->elem = num;
        parent->right->parent = parent;
        size++;
        return parent->right;
    }

    int set(node* currentnode, int element){
        if(!currentnode) throw new runtime_error("curretnode deoes not exist");

        int removedElem = currentnode->elem;
        currentnode->elem = element;
        return removedElem;
    }

    bool isLeaf(node* currentnode){
        if(currentnode->left || currentnode->right){
            return false;
        }

        return true;
    }

    void attach(node* currentnode, BinaryTree* tree1, BinaryTree* tree2){
        if(!isLeaf(currentnode)) throw new runtime_error("currentnode is not a leaf");

        currentnode->left = tree1->root;
        currentnode->right = tree2->root;

        if(tree1) tree1->root->parent = currentnode;
        if(tree2) tree2->root->parent = currentnode;

        tree1->root = nullptr;
        tree2->root = nullptr;
        return;
    }

    int remove(node* currentnode){
        if(!currentnode) throw runtime_error("current node is null");
        if(currentnode->left && currentnode->right) throw runtime_error("current node has two children");

        int removedElem = currentnode->elem;
        node* child = (currentnode->left)? currentnode->left : currentnode->right;

        if(currentnode->parent){
            if(!currentnode->parent->left){
                currentnode->parent->left = child;
            } else {
                currentnode->parent->right = child;
            }
        } else {
            root = currentnode;
        }

        child->parent = currentnode->parent;
        delete currentnode;
        size++;
        return removedElem;
    }

    bool searchrecursive(node* currentnode, int value){
        if(currentnode == nullptr) return false;
        if(currentnode->elem == value) return true;
        return searchrecursive(currentnode->left, value) || searchrecursive(currentnode->right, value);
    }

    void preorder_print(node* n){
        cout << n->elem << " ";
        if(n->left){
            preorder_print(n->left);
        }

        if(n->right){
            preorder_print(n->right);
        }
    }

    void inorder_print(node* n){
        if(n->left){
            inorder_print(n->left);
        }
        cout << n->elem << " ";
        if(n->right){
            inorder_print(n->right);
        }
    }

    void postorder_print(node* n){
        if(n->left){
            postorder_print(n->left);
        }

        if(n->right){
            postorder_print(n->right);
        }

        cout << n->elem << " ";
    }

};

int main(){
    BinaryTree* tree = new BinaryTree();

    try{
        node* root = tree->addroot(13);

        node* six = tree->addleft(root, 6);
        node* ten = tree->addright(root, 10);

        node* twenty = tree->addleft(six, 20);
        node* thirtyone = tree->addright(six, 31); 

        cout << "Preorder: " << endl;
        tree->preorder_print(root);
        cout << endl << "Inorder: " << endl;
        tree->inorder_print(root);
        cout << endl << "Postorder: " << endl;
        tree->postorder_print(root);
        cout << endl;

        (tree->searchrecursive(root,6))? cout << "True" : cout << "False";

    } catch (const exception& e){
        cout << e.what();
    }
}