#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Structure to represent a state in the state space
struct State {
    int m; // Missionaries on left bank
    int c; // Cannibals on left bank
    int b; // Boat position: 1 for left bank, 0 for right bank
    State* parent; // To trace the path
};

class MissionaryCannibal {
public:
    // Check if the current state is valid (no one gets eaten)
    bool isValid(int m, int c) {
        if (m < 0 || c < 0 || m > 3 || c > 3) return false; // Out of bounds
        if (m > 0 && m < c) return false; // Left bank check
        if (3 - m > 0 && (3 - m) < (3 - c)) return false; // Right bank check
        return true;
    }

    // Print the optimal path found by BFS
    void printSolution(State* goal) {
        vector<State*> path;
        for (State* cur = goal; cur != nullptr; cur = cur->parent) {
            path.push_back(cur);
        }
        
        cout << "\n--- Optimal State Space Path ---" << endl;
        cout << "(M_Left, C_Left, Boat) -> (M_Right, C_Right)\n";
        for (int i = path.size() - 1; i >= 0; --i) {
            State* s = path[i];
            string boatPos = (s->b == 1) ? "Left" : "Right";
            cout << "State: (" << s->m << ", " << s->c << ", " << boatPos << ")  ->  "
                 << "(" << 3 - s->m << ", " << 3 - s->c << ")\n";
        }
    }

    void solve() {
        queue<State*> q;
        bool visited[4][4][2] = {false};

        State* initial = new State{3, 3, 1, nullptr};
        q.push(initial);
        visited[3][3][1] = true;

        // Possible moves: (1M, 0C), (2M, 0C), (0M, 1C), (0M, 2C), (1M, 1C)
        int moves[5][2] = {{1, 0}, {2, 0}, {0, 1}, {0, 2}, {1, 1}};

        while (!q.empty()) {
            State* curr = q.front();
            q.pop();

            // Goal test
            if (curr->m == 0 && curr->c == 0 && curr->b == 0) {
                printSolution(curr);
                return;
            }

            // Generate next states
            for (int i = 0; i < 5; i++) {
                int next_m, next_c, next_b;
                
                if (curr->b == 1) { // Boat moving Left to Right
                    next_m = curr->m - moves[i][0];
                    next_c = curr->c - moves[i][1];
                    next_b = 0;
                } else { // Boat moving Right to Left
                    next_m = curr->m + moves[i][0];
                    next_c = curr->c + moves[i][1];
                    next_b = 1;
                }

                if (isValid(next_m, next_c) && !visited[next_m][next_c][next_b]) {
                    visited[next_m][next_c][next_b] = true;
                    State* nextState = new State{next_m, next_c, next_b, curr};
                    q.push(nextState);
                }
            }
        }
        cout << "No solution found." << endl;
    }
};

int main() {
    cout << "Starting Missionaries and Cannibals State Space Search...\n";
    MissionaryCannibal mc;
    mc.solve();
    return 0;
}