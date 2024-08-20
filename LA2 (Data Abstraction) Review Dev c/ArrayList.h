#include <iostream>
#include "List.h"
using namespace std;

class ArrayList: public List {
    int size = 0;
    int array[5];
    
    public:
    
    void add(int num){
        if(size >= 5){
            cout << "Array out of bounds" << endl;
            return;
        }
        
        array[size++] = num;
        return;
    }
    
    void print(){
        for(int i = 0; i < size; i++){
            cout << array[i] << " ";
        }
        
        cout << endl;
    }
    
    int removeAtpos(int pos){
    	int index = pos - 1;
    	int rem;
		for(int i = 0; i < size; i++){
			if(index == i){
				rem = array[i];
				for(int j = i; j < size; j++){
					array[j] = array[j+1];
				}
				size--;
			}
		}
		
		return rem; 
	}
	
	int removeAll(int num){
		int rem;
		for(int i = 0; i < size; i++){
			if(num == array[i]){
				rem = array[i];
				for(int j = i; j < size; j++){
					array[j] = array[j+1];
				}
				size--;
				i--;
			}
		}
		
		return rem; 
	}
	
	void addAtpos(int pos, int num){ // pos kay wala ni siya ga start sa 0
		size++;
		for(int i = size - 1; i > pos - 1; i--){
			array[i] = array[i-1];
		}
		
		array[pos - 1] = num;
	}

	void flip(){
		int temp = size - 1;
		int a = 0;
		for(int i = 0; i < size / 2; i++){
			int store = array[a];
			array[a] = array[temp];
			array[temp] = store;
			
			a++;
			temp--;
		}
	}
};
