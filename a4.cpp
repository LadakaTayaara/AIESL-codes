/*
 * Problem: Implementation of Minimax Algorithm for Tic-Tac-Toe Game
 * Subject: Artificial Intelligence and Expert Systems (AIES)
 * Algorithm: Adversarial Search (Minimax Algorithm)
 */

#include <iostream>
#include <algorithm>

using namespace std;

// Symbols used on the board
const char HUMAN = 'X';
const char AI = 'O';

// Structure to hold row and column coordinates of a move
struct Move {
    int row, col;
};

// Function to display current state of the 3x3 board
void printBoard(char b[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " " << b[i][0] << " | " << b[i][1] << " | " << b[i][2] << " \n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

// Check if any empty cell (' ') remains on the board
bool isMovesLeft(char b[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ') return true;
        }
    }
    return false;
}

// Utility / Evaluation function:
// Returns +10 if AI wins, -10 if Human wins, 0 if no winner yet
int evaluate(char b[3][3]) {
    // Check rows for a win
    for (int i = 0; i < 3; i++) {
        if (b[i][0] != ' ' && b[i][0] == b[i][1] && b[i][1] == b[i][2]) {
            return (b[i][0] == AI) ? +10 : -10;
        }
    }

    // Check columns for a win
    for (int j = 0; j < 3; j++) {
        if (b[0][j] != ' ' && b[0][j] == b[1][j] && b[1][j] == b[2][j]) {
            return (b[0][j] == AI) ? +10 : -10;
        }
    }

    // Check primary diagonal (top-left to bottom-right)
    if (b[0][0] != ' ' && b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        return (b[0][0] == AI) ? +10 : -10;
    }

    // Check secondary diagonal (top-right to bottom-left)
    if (b[0][2] != ' ' && b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        return (b[0][2] == AI) ? +10 : -10;
    }

    // No winner yet
    return 0;
}

// Recursive Minimax function
// depth: current depth in game tree (used to prefer faster wins / slower losses)
// isMax: true when it is AI's turn (Maximizer), false when Human's turn (Minimizer)
int minimax(char b[3][3], int depth, bool isMax) {
    int score = evaluate(b);

    // BASE CASES:
    // AI won: prefer win in fewer moves (higher score)
    if (score == 10) return score - depth;

    // Human won: prefer loss in more moves (delay defeat)
    if (score == -10) return score + depth;

    // No moves left: Draw (tie)
    if (!isMovesLeft(b)) return 0;

    // RECURSIVE CASES:
    if (isMax) {
        // Maximizer's turn (AI wants to maximize score)
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == ' ') {
                    b[i][j] = AI; // Make move
                    best = max(best, minimax(b, depth + 1, false));
                    b[i][j] = ' '; // Undo move (Backtrack)
                }
            }
        }
        return best;
    } else {
        // Minimizer's turn (Human wants to minimize score)
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] == ' ') {
                    b[i][j] = HUMAN; // Make move
                    best = min(best, minimax(b, depth + 1, true));
                    b[i][j] = ' '; // Undo move (Backtrack)
                }
            }
        }
        return best;
    }
}

// Evaluates all available moves for AI and returns the optimal move
Move findBestMove(char b[3][3]) {
    int bestVal = -1000;
    Move bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ') {
                b[i][j] = AI; // Try move
                int moveVal = minimax(b, 0, false);
                b[i][j] = ' '; // Undo move

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
    // Initialize 3x3 board with spaces
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

    // Main game loop: continue while moves are left and no winner exists
    while (isMovesLeft(board) && evaluate(board) == 0) {
        if (humanTurn) {
            int move;
            cout << "Enter your move (1-9): ";
            cin >> move;

            // Convert 1-9 cell number to 2D row and column indices
            int r = (move - 1) / 3;
            int c = (move - 1) % 3;

            // Validate move
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
        humanTurn = !humanTurn; // Switch turn
    }

    // Check and display the final game outcome
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
