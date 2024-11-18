#include <iostream>
#include <stack>
using namespace std;

bool isValid(int* array, int size){
    stack<int> Stack;
    int lowerbound = -1;

    for(int i = 0; i < size; i++){
        if(array[i] < lowerbound){
            return false;
        }

        while(!Stack.empty() && array[i] > Stack.top()){
            lowerbound  = Stack.top();
            Stack.pop();
        }

        Stack.push(array[i]);
    }

    return true;

}

int main(){
    int array[] = {50, 55, 100, 200, 53};
    int size = sizeof(array) / sizeof(array[0]);
    
    cout << isValid(array, size);
}