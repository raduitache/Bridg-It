#include "Backend.hpp"
#include "UI.hpp"
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

bool isClickValid(sf::Event::MouseButtonEvent mouse){
    int x = int(mouse.x / (rowDist / 2));
    int y = int(mouse.y / (colDist / 2));
    cout << x << " " << y << endl;
    if(board[y][x] == 'x' && playerRound == 0) return 1;
    if(board[y][x] == 'y' && playerRound == 1) return 1;
    return 0;
}

void linkIfValid(sf::Event::MouseButtonEvent click1, sf::Event::MouseButtonEvent click2){
    int x1 = int(click1.x / (rowDist / 2));
    int y1 = int(click1.y / (colDist / 2));
    int x2 = int(click2.x / (rowDist / 2));
    int y2 = int(click2.y / (colDist / 2));
    if(x1 == x2){
        if(abs(y1 - y2) == 2){
            if(board[(y1 + y2) / 2][x1] == '0'){
                board[(y1 + y2) / 2][x1] = '0' + playerRound + 1;
                playerRound = !playerRound;
            }
        }
    }
    if(y1 == y2){
        if(abs(x1 - x2) == 2){
            if(board[y1][(x1 + x2) / 2] == '0'){
                board[y1][(x1 + x2) / 2] = '0' + playerRound + 1;
                playerRound = !playerRound;
            }
        }
    }
    printBoard();
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
    if(isClickValid(mouse)){
            // wait for the second click:
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        linkIfValid(mouse, event.mouseButton);
                        return;
                    }
                }
            }

            window.clear();
            loadBoard(window);
            window.display();
        }
    }

}
