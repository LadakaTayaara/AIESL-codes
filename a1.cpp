/*
 * Problem: 8-Puzzle Problem using A* Algorithm
 * Subject: AIES (SPPU)
 * Heuristic Used: Manhattan Distance
 */

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <string>

using namespace std;

// Define the Goal State
const vector<vector<int>> GOAL_STATE = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0} // 0 represents the blank space
};

// Node structure to represent each state in the search space
struct Node {
    vector<vector<int>> board;
    int blank_row, blank_col;
    int g; // Cost to reach this node (number of moves)
    int h; // Heuristic cost (Manhattan distance to goal)
    int f; // Total cost (f = g + h)
    Node* parent;

    // Constructor to initialize a node
    Node(vector<vector<int>> b, int r, int c, int g_cost, int h_cost, Node* p) {
        board = b;
        blank_row = r;
        blank_col = c;
        g = g_cost;
        h = h_cost;
        f = g + h;
        parent = p;
    }
};

// Custom Comparator for the Priority Queue (Min-Heap based on f value)
struct CompareNode {
    bool operator()(Node* const& n1, Node* const& n2) {
        return n1->f > n2->f;
    }
};

class EightPuzzleAStar {
private:
    // Helper function to convert 2D board to string for the 'visited' set
    string boardToString(const vector<vector<int>>& board) {
        string s = "";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                s += to_string(board[i][j]);
            }
        }
        return s;
    }

    // Calculate Manhattan Distance Heuristic
    int calculateManhattan(const vector<vector<int>>& board) {
        int distance = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int value = board[i][j];
                if (value != 0) {
                    // Find target position of the current value in the goal state
                    int target_row = (value - 1) / 3;
                    int target_col = (value - 1) % 3;
                    distance += abs(i - target_row) + abs(j - target_col);
                }
            }
        }
        return distance;
    }

    // Print the board state
    void printBoard(const vector<vector<int>>& board) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) cout << "_ ";
                else cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << "------" << endl;
    }

    // Trace back from goal to start and print the path
    void printSolution(Node* goalNode) {
        vector<Node*> path;
        Node* current = goalNode;
        while (current != nullptr) {
            path.push_back(current);
            current = current->parent;
        }

        cout << "\nOptimal Path Found in " << path.size() - 1 << " moves:\n\n";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << "Step " << (path.size() - 1) - i << " (g=" << path[i]->g 
                 << ", h=" << path[i]->h << ", f=" << path[i]->f << "):" << endl;
            printBoard(path[i]->board);
        }
    }

public:
    void solve(vector<vector<int>> initialBoard) {
        // Find initial position of the blank tile (0)
        int start_r = -1, start_c = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (initialBoard[i][j] == 0) {
                    start_r = i;
                    start_c = j;
                }
            }
        }

        // Priority Queue for Open List
        priority_queue<Node*, vector<Node*>, CompareNode> openList;
        
        // Set for Closed List to keep track of visited states
        set<string> visited;

        // Create the root node
        int h_initial = calculateManhattan(initialBoard);
        Node* root = new Node(initialBoard, start_r, start_c, 0, h_initial, nullptr);
        openList.push(root);

        // Movement arrays for Up, Down, Left, Right
        int row_moves[] = {-1, 1, 0, 0};
        int col_moves[] = {0, 0, -1, 1};

        cout << "Searching for solution using A*..." << endl;

        while (!openList.empty()) {
            // Get the node with the lowest f value
            Node* current = openList.top();
            openList.pop();

            string currentBoardStr = boardToString(current->board);

            // Goal test
            if (current->board == GOAL_STATE) {
                printSolution(current);
                return;
            }

            // Skip if already visited
            if (visited.find(currentBoardStr) != visited.end()) {
                continue;
            }
            visited.insert(currentBoardStr);

            // Generate child states by moving the blank tile
            for (int i = 0; i < 4; i++) {
                int new_r = current->blank_row + row_moves[i];
                int new_c = current->blank_col + col_moves[i];

                // Check bounds
                if (new_r >= 0 && new_r < 3 && new_c >= 0 && new_c < 3) {
                    vector<vector<int>> new_board = current->board;
                    // Swap blank tile with adjacent tile
                    swap(new_board[current->blank_row][current->blank_col], new_board[new_r][new_c]);

                    if (visited.find(boardToString(new_board)) == visited.end()) {
                        int h_new = calculateManhattan(new_board);
                        Node* child = new Node(new_board, new_r, new_c, current->g + 1, h_new, current);
                        openList.push(child);
                    }
                }
            }
        }
        cout << "No solution exists for this initial configuration." << endl;
    }
};

int main() {
    // A solvable initial configuration
    vector<vector<int>> initial_state = {
        {2, 8, 3},
        {1, 6, 4},
        {7, 0, 5}
    };

    cout << "8-Puzzle A* Algorithm Initialized." << endl;
    cout << "Initial Board State:" << endl;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++) {
            if(initial_state[i][j] == 0) cout << "_ ";
            else cout << initial_state[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------\n";

    EightPuzzleAStar puzzle;
    puzzle.solve(initial_state);

    return 0;
}