#include "AI.hpp"

void miscareEasyPc(){
     int ok=0;

    for(int i=1;i<2 * boardSize - 1&&!ok;i++)
        for(int j=0;j< 2 * (boardSize-1)&&!ok;j++)
            if(board[i][j]=='0')
            {
                board[i][j]='0'+2;
                ok=1;
            }
}

void miscareMediumPC(){
    bool **vizitate = new bool*[2 * boardSize - 1];
    for(int i = 0; i < 2 * boardSize - 1; i++)
        vizitate[i] = new bool[2 * boardSize - 1];

    for(int i = 1; i < 2 * (boardSize - 1); i += 2){
        for(int k = 0; k < 2 * boardSize - 1; k ++){
            for(int l = 0; l < 2 * boardSize - 1; l++){
                vizitate[k][l] = false;
            }
        }
        int toSetX = -1, toSetY = -1;
        vizitate[i][0] = true;
        if(foundWay(i, 0, toSetX, toSetY, vizitate)){
            board[toSetX][toSetY] = '2';
            return;
        }
    }
}

bool foundWay(int x, int y, int &validX, int &validY, bool **vizitate){
    if(y == 2 * (boardSize - 1))
        return true;

    if(y < 2 * (boardSize - 1)){
        if(board[x][y + 1] == '0' && !vizitate[x][y + 2]){
            vizitate[x][y + 2] = true;
            if(validX == -1 && validY == -1){
                validX = x;
                validY = y + 1;
                if(foundWay(x, y + 2, validX, validY, vizitate))
                    return true;
                validX = -1;
                validY = -1;
            }
            else if(foundWay(x, y + 2, validX, validY, vizitate))
                return true;
        }
        else if(board[x][y + 1] == '2' && !vizitate[x][y + 2]){
            vizitate[x][y + 2] = true;
            if(foundWay(x, y + 2, validX, validY, vizitate))
                return true;
        }
    }

    if(x > 1){
        if(board[x - 1][y] == '0' && !vizitate[x - 2][y]){
            vizitate[x - 2][y] = true;
            if(validX == -1 && validY == -1){
                validX = x - 1;
                validY = y;
                if(foundWay(x - 2, y, validX, validY, vizitate))
                    return true;
                validX = -1;
                validY = -1;
            }
            if(foundWay(x - 2, y, validX, validY, vizitate))
                return true;
        }
        else if(board[x - 1][y] == '2' && !vizitate[x - 2][y]){
            vizitate[x - 2][y] = true;
            if(foundWay(x - 2, y, validX, validY, vizitate))
                return true;
        }
    }

    if(x < 2 * boardSize - 3){
        if(board[x + 1][y] == '0' && !vizitate[x + 2][y]){
            vizitate[x + 2][y] = true;
            if(validX == -1 && validY == -1){
                validX = x + 1;
                validY = y;
                if(foundWay(x + 2, y, validX, validY, vizitate))
                    return true;
                validX = -1;
                validY = -1;
            }
            else if(foundWay(x + 2, y, validX, validY, vizitate))
                return true;
        }
        else if(board[x + 1][y] == '2' && !vizitate[x + 2][y]){
            vizitate[x + 2][y] = true;
            if(foundWay(x + 2, y, validX, validY, vizitate))
                return true;
        }
    }

    if(y > 0){
        if(board[x][y - 1] == '0' && !vizitate[x][y - 2]){
            vizitate[x][y - 2] = true;
            if(validX == -1 && validY == -1){
                validX = x;
                validY = y - 1;
                if(foundWay(x, y - 2, validX, validY, vizitate))
                    return true;
                validX = -1;
                validY = -1;
            }
            else if(foundWay(x, y - 2, validX, validY, vizitate))
                return true;
        }
        else if(board[x][y - 1] == '2' && !vizitate[x][y - 2]){
            vizitate[x][y - 2] = true;
            if(foundWay(x, y - 2, validX, validY, vizitate))
                return true;
        }
    }

    return false;
}
