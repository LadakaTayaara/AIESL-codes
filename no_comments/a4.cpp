#include <iostream>
#include <algorithm>

using namespace std;

const char HUMAN = 'X';
const char AI = 'O';

struct Move {
    int row, col;
};

void printBoard(char b[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " " << b[i][0] << " | " << b[i][1] << " | " << b[i][2] << " \n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool isMovesLeft(char b[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ') return true;
        }
    }
    return false;
}

int evaluate(char b[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (b[i][0] != ' ' && b[i][0] == b[i][1] && b[i][1] == b[i][2]) {
            return (b[i][0] == AI) ? +10 : -10;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (b[0][j] != ' ' && b[0][j] == b[1][j] && b[1][j] == b[2][j]) {
            return (b[0][j] == AI) ? +10 : -10;
        }
    }

    if (b[0][0] != ' ' && b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        return (b[0][0] == AI) ? +10 : -10;
    }

    if (b[0][2] != ' ' && b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        return (b[0][2] == AI) ? +10 : -10;
    }

    return 0;
}

int minimax(char b[3][3], int depth, bool isMax) {
    int score = evaluate(b);

    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft(b)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == ' ') {
                    b[i][j] = AI;
                    best = max(best, minimax(b, depth + 1, false));
                    b[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == ' ') {
                    b[i][j] = HUMAN;
                    best = min(best, minimax(b, depth + 1, true));
                    b[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

Move findBestMove(char b[3][3]) {
    int bestVal = -1000;
    Move bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ') {
                b[i][j] = AI;
                int moveVal = minimax(b, 0, false);
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
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    cout << "=== Tic-Tac-Toe using Minimax AI ===\n";
    cout << "Grid reference positions:\n";
    cout << " 1 | 2 | 3 \n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6 \n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9 \n\n";

    char choice;
    cout << "Do you want to play first? (y/n): ";
    cin >> choice;
    bool humanTurn = (choice == 'y' || choice == 'Y');

    while (isMovesLeft(board) && evaluate(board) == 0) {
        if (humanTurn) {
            int move;
            cout << "Enter your move (1-9): ";
            cin >> move;

            int r = (move - 1) / 3;
            int c = (move - 1) % 3;

            if (move < 1 || move > 9 || board[r][c] != ' ') {
                cout << "Invalid move! Please try an empty cell between 1 and 9.\n";
                continue;
            }

            board[r][c] = HUMAN;
        } else {
            cout << "AI is calculating optimal move...\n";
            Move best = findBestMove(board);
            board[best.row][best.col] = AI;
            cout << "AI plays at position " << (best.row * 3 + best.col + 1) << ":\n";
        }

        printBoard(board);
        humanTurn = !humanTurn;
    }

    int finalScore = evaluate(board);
    if (finalScore == 10) {
        cout << "Result: AI wins!\n";
    } else if (finalScore == -10) {
        cout << "Result: You win!\n";
    } else {
        cout << "Result: It's a draw!\n";
    }

    return 0;
}
