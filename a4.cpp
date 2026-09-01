#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "--+---+--\n";
    }
}

char checkWinner(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return ' ';

    return 'T';
}

int minimax(vector<vector<char>>& board, int depth, bool isMaximizing) {
    char result = checkWinner(board);
    if (result == 'O') return 1;
    if (result == 'X') return -1;
    if (result == 'T') return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(board, depth + 1, false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(board, depth + 1, true);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

pair<int, int> bestMove(vector<vector<char>>& board) {
    int bestScore = numeric_limits<int>::min();
    pair<int, int> move = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(board, 0, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    move = {i, j};
                }
            }
        }
    }
    return move;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' '));

    while (true) {
        printBoard(board);

        int r, c;
        while (true) {
            cout << "Enter row and col (0-2): ";
            if (cin >> r >> c && r >= 0 && r < 3 && c >= 0 && c < 3 && board[r][c] == ' ') {
                board[r][c] = 'X';
                break;
            }
            cout << "Invalid move, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (checkWinner(board) != ' ') break;

        pair<int, int> ai = bestMove(board);
        if (ai.first != -1) {
            board[ai.first][ai.second] = 'O';
        }

        if (checkWinner(board) != ' ') break;
    }

    printBoard(board);
    char winner = checkWinner(board);

    if (winner == 'T') {
        cout << "It's a tie!\n";
    } else {
        cout << winner << " wins!\n";
    }

    return 0;
}
