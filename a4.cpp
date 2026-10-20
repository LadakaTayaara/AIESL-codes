/*
 * Problem: Tic-Tac-Toe using Minimax Algorithm
 * Subject: AIES (SPPU)
 * Symbols: Human = 'X', AI = 'O'
 */

#include <iostream>
#include <algorithm>

using namespace std;

char b[3][3];

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " " << b[i][0] << " | " << b[i][1] << " | " << b[i][2] << " \n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

// Returns +10 if AI ('O') wins, -10 if Human ('X') wins, 0 otherwise
int evaluate() {
    for (int i = 0; i < 3; i++) {
        // Check Rows and Columns
        if (b[i][0] != ' ' && b[i][0] == b[i][1] && b[i][1] == b[i][2])
            return (b[i][0] == 'O') ? 10 : -10;
        if (b[0][i] != ' ' && b[0][i] == b[1][i] && b[1][i] == b[2][i])
            return (b[0][i] == 'O') ? 10 : -10;
    }
    // Check Diagonals
    if (b[0][0] != ' ' && b[0][0] == b[1][1] && b[1][1] == b[2][2])
        return (b[0][0] == 'O') ? 10 : -10;
    if (b[0][2] != ' ' && b[0][2] == b[1][1] && b[1][1] == b[2][0])
        return (b[0][2] == 'O') ? 10 : -10;

    return 0;
}

// Unified Minimax: AI maximizes ('O'), Human minimizes ('X')
int minimax(bool isAI) {
    int score = evaluate();
    if (score != 0) return score;

    bool movesLeft = false;
    int best = isAI ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ') {
                movesLeft = true;
                b[i][j] = isAI ? 'O' : 'X';
                int val = minimax(!isAI);
                b[i][j] = ' ';
                best = isAI ? max(best, val) : min(best, val);
            }
        }
    }
    return movesLeft ? best : 0;
}

pair<int, int> findBestMove() {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ') {
                b[i][j] = 'O';
                int moveVal = minimax(false);
                b[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

int main() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) b[i][j] = ' ';

    cout << "=== Tic-Tac-Toe using Minimax AI ===\n";
    cout << "Grid reference positions:\n";
    cout << " 1 | 2 | 3 \n---|---|---\n 4 | 5 | 6 \n---|---|---\n 7 | 8 | 9 \n\n";

    char choice;
    cout << "Do you want to play first? (y/n): ";
    cin >> choice;
    bool humanTurn = (choice == 'y' || choice == 'Y');

    while (evaluate() == 0) {
        bool movesLeft = false;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (b[i][j] == ' ') movesLeft = true;
        if (!movesLeft) break;

        if (humanTurn) {
            int move;
            cout << "Enter your move (1-9): ";
            cin >> move;
            int r = (move - 1) / 3, c = (move - 1) % 3;

            if (move < 1 || move > 9 || b[r][c] != ' ') {
                cout << "Invalid move! Please try an empty cell between 1 and 9.\n";
                continue;
            }
            b[r][c] = 'X';
        } else {
            cout << "AI is calculating optimal move...\n";
            pair<int, int> best = findBestMove();
            b[best.first][best.second] = 'O';
            cout << "AI plays at position " << (best.first * 3 + best.second + 1) << ":\n";
        }

        printBoard();
        humanTurn = !humanTurn;
    }

    int finalScore = evaluate();
    if (finalScore == 10) cout << "Result: AI wins!\n";
    else if (finalScore == -10) cout << "Result: You win!\n";
    else cout << "Result: It's a draw!\n";

    return 0;
}
