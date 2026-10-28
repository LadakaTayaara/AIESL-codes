/*
 * Problem: Tic-Tac-Toe Game (Assignment 4)
 * Algorithm: Adversarial Search - Minimax Algorithm
 *
 * Game Rules:
 * - 3x3 Grid with 9 cells (1 to 9).
 * - Human player is 'X' (Minimizing player, score = -10).
 * - AI player is 'O' (Maximizing player, score = +10).
 * - Draw game yields score = 0.
 *
 * Minimax Principle:
 * - In two-player zero-sum games, AI aims to maximize the score (+10),
 *   while the human player is assumed to play optimally to minimize the score (-10).
 * - Terminal evaluation:
 *     AI wins  => +10
 *     Human wins => -10
 *     Draw     => 0
 * - AI evaluates all possible future game states recursively to choose
 *   the move leading to the best possible guaranteed outcome.
 */

#include <iostream>
using namespace std;

char b[9]; // 1D array representing the 3x3 Tic-Tac-Toe board (cells 0 to 8)

// Checks the board for any 3-in-a-row winning condition:
// Returns +10 if AI ('O') has won, -10 if Human ('X') has won, or 0 if no winner yet
int check() {
    // 8 possible winning triplets: 3 rows, 3 columns, 2 diagonals
    int w[][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // Rows
        {0,3,6}, {1,4,7}, {2,5,8}, // Columns
        {0,4,8}, {2,4,6}           // Diagonals
    };

    for (auto &l : w)
        if (b[l[0]] != ' ' && b[l[0]] == b[l[1]] && b[l[1]] == b[l[2]])
            return b[l[0]] == 'O' ? 10 : -10;

    return 0; // No winner yet
}

// Recursive Minimax decision engine:
// isAI = true  => AI's turn (Maximizing player: tries to maximize score)
// isAI = false => Human's turn (Minimizing player: tries to minimize score)
int minimax(bool isAI) {
    int score = check();
    // If a terminal win/loss state is reached, return its utility score (+10 or -10)
    if (score) return score;

    int best = isAI ? -100 : 100;
    bool full = true; // Tracks if all cells are filled (draw detection)

    // Traverse all 9 cells to simulate moves
    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') {
            full = false;
            b[i] = isAI ? 'O' : 'X';   // Simulate move

            int v = minimax(!isAI);    // Recurse for the opponent's best response

            b[i] = ' ';                // Undo simulated move (backtrack)

            // Maximizer picks maximum score, Minimizer picks minimum score
            best = isAI ? max(best, v) : min(best, v);
        }
    }

    // If board is completely filled and no winner, it is a Draw (score 0)
    return full ? 0 : best;
}

int main() {
    // Initialize the board with empty spaces
    for (int i = 0; i < 9; i++) b[i] = ' ';

    int m;
    cout << "Tic-Tac-Toe! Enter move (1-9):\n";

    // Game loop: runs while no winner exists and input is available
    while (!check() && cin >> m) {
        // Validate move: must be between 1 and 9, and the cell must be empty
        if (m < 1 || m > 9 || b[m - 1] != ' ') {
            cout << "Invalid move, try again: ";
            continue;
        }

        // Apply Human's move ('X')
        b[m - 1] = 'X';

        // Check if Human just won or if board is full before AI moves
        if (check() == -10) { cout << "You win!\n"; break; }

        // Find the best move for AI ('O') using Minimax
        int best = -100, move = -1;
        for (int i = 0; i < 9; i++) {
            if (b[i] == ' ') {
                b[i] = 'O';                 // Simulate AI move
                int v = minimax(false);     // Evaluate opponent's response
                b[i] = ' ';                 // Undo move

                if (v > best) {             // Keep the move with highest utility
                    best = v;
                    move = i;
                }
            }
        }

        // Apply AI's optimal move
        if (move != -1) b[move] = 'O';

        // Print current board state
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < 9; i++)
            cout << b[i] << (i % 3 == 2 ? "\n" : " | ");
        cout << "\n";

        // Check terminal conditions
        if (check() == 10) { cout << "AI wins!\n"; break; }
    }
}
