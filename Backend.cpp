#include "Backend.hpp"
#include <iostream>

using namespace std;


void addDotsToBoard(){
    for(int i = 0; i < 2 * boardSize - 1; i++){
        for(int j = 0; j < 2 * boardSize - 1; j++){
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
    board[0][2 * boardSize - 2] = '-';
    board[2 * boardSize - 2][0] = '-';
    board[2 * boardSize - 2][2 * boardSize - 2] = '-';
}

void printBoard(){
    for(int i = 0; i < 2 * boardSize - 1; i++){
        for(int j = 0; j < 2 * boardSize - 1; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void createBoard(){
    board = new char*[2 * boardSize - 1];
    for(int i = 0; i < 2 * boardSize - 1; i++){
        board[i] = new char[2 * boardSize - 1];
    }
    addDotsToBoard();
    printBoard();
}

void linkDots(sf::Event::MouseButtonEvent mouse){

}
