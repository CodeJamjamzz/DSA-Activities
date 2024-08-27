#include <iostream>
#include <string>
using namespace std;

struct Entry{
    string name;
    int score;
    string college;
};

struct Scoreboard{
    Entry board[5];
    int size = 0;

    bool add(Entry e){
        int i;
        for(i = 0; i < size; i++){
            if(board[i].score < e.score){
                break;
            }
        }

        if(i >= 5){
            return false;
        } else if(size >= 5){
            size = 4;
        }

        for(int j = size; j > i; j--){
            board[j] = board[j-1];
        }

        board[i] = e;
        size++;

        return true;
    }

    void print(){
        for(int i = 0; i < size; i++){
            cout << "Name: " << board[i].name << endl;
            cout << "Score: " << board[i].score << endl;
            cout << "College: " << board[i].college << endl;
            cout << endl;
        }
    }
};

int main(){
    Entry e;
    Scoreboard score;

    char op;


    do {
        
        cout << "Option: ";
        cin >> op;

        switch (op){
            case 'a':
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, e.name);

                cout << "Enter score: ";
                cin >> e.score;

                cout << "Enter college: ";
                cin.ignore();
                getline(cin, e.college);

                score.add(e);

                break;
            case 'p':
                score.print();
                break;
            case 'x':
                cout << "Exiting...";
                break;
        }

    } while (op != 'x');

}