#include "Backend.hpp"
#include "globalVars.hpp"
#include <iostream>

using namespace std;


void addDotsToBoard(int n){
    for(int i = 0; i < 2 * n - 1; i++){
        for(int j = 0; j < 2 * n - 1; j++){
            if((i + j) % 2 == 0){
                board[i][j] = '0';
            }
            else if(i % 2 == 0 && j % 2 == 1){
                board[i][j] = 'x';
            }
            else{
                board[i][j] = 'y';
            }
        }
    }
    board[0][0] = '-';
    board[0][2 * n - 2] = '-';
    board[2 * n - 2][0] = '-';
    board[2 * n - 2][2 * n - 2] = '-';
}

void printBoard(int n){
    for(int i = 0; i < 2 * n - 1; i++){
        for(int j = 0; j < 2 * n - 1; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void createBoard(int n){
    board = new char*[2 * n - 1];
    for(int i = 0; i < 2 * n - 1; i++){
        board[i] = new char[2 * n - 1];
    }
    cout << "Si asta a mers" << endl;
    addDotsToBoard(n);
    cout << "Am terminat tot si nu stiu care mai e problema" << endl;
    printBoard(n);
}
