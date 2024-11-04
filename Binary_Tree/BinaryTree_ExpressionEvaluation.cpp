#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;

struct node{
    string elem;
    node* parent;
    node* left;
    node* right;
};

class BinaryTree {
    node* root;
    int size;

    public:
    BinaryTree(): root(nullptr), size(0){}

    node* addRoot(string input){
        if(root) throw logic_error("There is already a root");

        root = new node();
        root->elem = input;
        size++;
        return root;
    }

    node* addLeft(node* currentnode, string input){
        if(currentnode->left) throw logic_error("There is already a left child");

        currentnode->left = new node();
        currentnode->left->elem = input;
        currentnode->left->parent = currentnode;
        size++;
        return currentnode->left;
    }

    node* addRight(node* currentnode, string input){
        if(currentnode->right) throw logic_error("There is already a right child");

        currentnode->right = new node();
        currentnode->right->elem = input;
        currentnode->right->parent = currentnode;
        size++;
        return currentnode->right;
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

    int expressionTraveral(node* currentnode){
        if(!currentnode->left && !currentnode->right){
            return stoi(currentnode->elem);
        }

        int left, right;
        if(currentnode->left) left = expressionTraveral(currentnode->left);
        if(currentnode->right) right = expressionTraveral(currentnode->right);

        if (currentnode->elem == "+")  
            return left + right;
        else if (currentnode->elem == "-")
            return left - right;
        else if (currentnode->elem == "*")
            return left * right;
        else if (currentnode->elem == "/") {
            if (right == 0) {
                cout << "Cannot divide by 0"; 
                return 0;
            }
            return left / right;
        }
    }


    bool expressionEvaluation(node* currentnode){
        if(!currentnode->left && !currentnode->right){
            string element = currentnode->elem;
            if(element == "+" || element == "-" || element == "*" || element == "/"){
                return false;
            }

            cout << currentnode->elem << " ";
            return true;
        }

        cout << currentnode->elem << " ";

        bool left = true, right = true;
        if(currentnode->left){
            left = expressionEvaluation(currentnode->left);
        }

        if(currentnode->right){
            right = expressionEvaluation(currentnode->right);
        }

        return left || right;
    }

    node* evaluate(string posfix){
        stack<node*> stacks;

        for(char ch: posfix){
            node* newnode = new node();
            newnode->elem = string(1,ch);

            if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                newnode->left = stacks.top(); stacks.pop();  // Left operand
                newnode->right = stacks.top(); stacks.pop(); // Right operand
            }

            stacks.push(newnode);
        }

        return stacks.top();
    }

};

int main(){
    BinaryTree* tree = new BinaryTree();

    node* root = tree->addRoot("+");

    node* times = tree->addLeft(root, "*");
    node* plus = tree->addRight(root, "+");

    node* six = tree->addLeft(times, "6");
    node* five= tree->addRight(times, "5");

    node* ten = tree->addLeft(plus, "10");
    node* twenty = tree->addRight(plus, "20");

    tree->Breadth_FirstSearch_Traversal(root); cout << endl;
    cout << tree->expressionTraveral(root); cout << endl;
    (tree->expressionEvaluation(root))? cout << endl << "True" : cout << endl << "False"; cout << endl;

    node* tr = tree->evaluate("AB+C*");
    tree->Breadth_FirstSearch_Traversal(tr); cout << endl;
}