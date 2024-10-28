#include <iostream>
using namespace std;

struct node{
    node** children;
    int num_child;
    node* parent;
    int elem;

    node(){
        num_child = 0;
        children = (node**) calloc(num_child,sizeof(node*));
        parent = nullptr;
        elem = 0;
    }

    node(int num){
        num_child = 0;
        children = (node**) calloc(0,sizeof(node*));
        parent = nullptr;
        elem = num;
    }
};

class BinaryTree {
    node* root;
    int size;

    public:
    BinaryTree(){
        root = nullptr;
        size = 0;
    }

    node* addRoot(int num){
        if(root != nullptr){
            throw runtime_error(to_string(num) + "cannot be a root" );
        }

        root = new node(num);
        size++;
        return root;
    }

    node* addChild(node* currentnode, int elem){
        currentnode->num_child++;
        currentnode->children = (node**) realloc(currentnode->children,currentnode->num_child*sizeof(node*));
        int index = currentnode->num_child - 1;
        currentnode->children[index]->elem = elem;
        return currentnode->children[index];
    }

    int remove(node* currentnode){
        if(!currentnode) throw runtime_error("node is null");
        if(currentnode->num_child >= 2) throw runtime_error("node has more than 1 children");

        if(currentnode->num_child == 0){

            if(currentnode->parent){
                currentnode->parent->num_child = 0;
            } else {
                root = nullptr;
            }

        } else {
            int child = currentnode->children[0]->elem;
            if(currentnode->parent){
                addChild(currentnode->parent, child);
            } else {
                root = currentnode->children[0];
            }
        }

        int removed = currentnode->elem;
        delete currentnode;
        return removed;
    }

};

int main(){
    BinaryTree* tree = new BinaryTree();

    node* root = tree->addRoot(5);
    node* six = tree->addChild(root, 6);
    node* seven = tree->addChild(root, 7);
}