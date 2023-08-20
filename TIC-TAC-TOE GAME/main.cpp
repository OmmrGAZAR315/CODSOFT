#include <iostream>

using namespace std;

void printBoard(char element[3][3]);

bool checkWin(char element[3][3]);

void beginning(char element[3][3]);

bool isItDraw(char element[3][3]);


int main() {
    char currentPlayer = 'X';
    bool X_turn = true;
    char elements[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
    };
    printBoard(elements);
    while (true) {
        int choice, row = 0, column;
        if (isItDraw(elements))
            goto replay;
        cout << currentPlayer << " turn\n";
        cin >> choice;
        if (0 > choice || choice >= 10) break;
        while (choice - 3 > 0) {
            choice -= 3;
            row++;
        }
        column = choice - 1;
        if (elements[row][column] == ' ') {
            elements[row][column] = currentPlayer;
            X_turn = !X_turn;
        } else {
            cout << "already has been chosen\n";
        }
        if (checkWin(elements)) {
            printBoard(elements);
            cout << " Winner Winner chicken dinner\n\n";
            replay:
            cout << "Do you want play again? (Y or N)  \n";
            cin >> currentPlayer;
            if (tolower(currentPlayer) == 'y') {
                beginning(elements);
                X_turn = true;
            } else break;
        }
        if (X_turn)
            currentPlayer = 'X';
        else currentPlayer = 'O';
        printBoard(elements);
    }
}

void beginning(char elements[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            elements[i][j] = ' ';
        }
    }
}

void printBoard(char element[3][3]) {
    for (int r = 0; r < 3; r++) {
        cout << "|";
        for (int c = 0; c < 3; c++) {
            cout << element[r][c] << " |";
        }
        cout << endl;
        for (int u = 0; u < 3 && r != 2; u++) {
            cout << "|--";
        }
        if (r != 2) cout << "|" << endl;
    }

}

bool checkWin(char element[3][3]) {
    for (int r = 0; r < 3; r++) {
        if (element[r][0] == element[r][1] && element[r][1] == element[r][2] && element[r][0] != ' ') {
            for (int i = 0; i < 3; i++)
                element[r][i] = '-';
            return true;
        }
    }
    for (int c = 0; c < 3; c++) {
        if (element[0][c] == element[1][c] && element[1][c] == element[2][c] && element[0][c] != ' ') {
            for (int i = 0; i < 3; i++)
                element[i][c] = '|';
            return true;
        }
    }
    if (element[0][0] == element[1][1] && element[1][1] == element[2][2] && element[0][0] != ' ') {
        for (int i = 0; i < 3; ++i)
            element[i][i] = '\\';
        return true;
    }
    if (element[0][2] == element[1][1] && element[1][1] == element[2][0] && element[2][2] != ' ') {
        element[0][2] = '/';
        element[1][1] = '/';
        element[2][0] = '/';
        return true;
    }
    return false;
}

bool isItDraw(char elements[3][3]) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (elements[r][c] == ' ')
                return false;
        }
    }
    cout<<"Draw...";
    return true;
}
