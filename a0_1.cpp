/*
 * Missionaries and Cannibals Problem using BFS
 * State: (m, c, b)
 * m: Missionaries on left bank (0-3)
 * c: Cannibals on left bank (0-3)
 * b: Boat on left bank (1 = Left, 0 = Right)
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State {
    int m, c, b;
    vector<State> path;
};

// Check if state is valid (missionaries never outnumbered on either bank)
bool isValid(int m, int c) {
    if (m < 0 || c < 0 || m > 3 || c > 3) return false;
    if (m > 0 && m < c) return false;                 // Left bank check
    if (3 - m > 0 && (3 - m) < (3 - c)) return false; // Right bank check
    return true;
}

int main() {
    queue<State> q;
    bool vis[4][4][2] = {false};

    // Start with 3M, 3C, boat on left bank
    q.push({3, 3, 1, {{3, 3, 1}}});
    vis[3][3][1] = true;

    // 5 possible boat moves: (1M,0C), (2M,0C), (0M,1C), (0M,2C), (1M,1C)
    int moves[5][2] = {{1, 0}, {2, 0}, {0, 1}, {0, 2}, {1, 1}};

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        // Goal: 0M, 0C, boat on right bank
        if (cur.m == 0 && cur.c == 0 && cur.b == 0) {
            cout << "\n--- Optimal State Space Path ---\n";
            cout << "(M_Left, C_Left, Boat) -> (M_Right, C_Right)\n";
            for (auto &s : cur.path) {
                cout << "State: (" << s.m << ", " << s.c << ", " << (s.b ? "Left" : "Right")
                     << ") -> (" << 3 - s.m << ", " << 3 - s.c << ")\n";
            }
            return 0;
        }

        for (auto &mv : moves) {
            int nm = cur.b ? cur.m - mv[0] : cur.m + mv[0];
            int nc = cur.b ? cur.c - mv[1] : cur.c + mv[1];
            int nb = 1 - cur.b;

            if (isValid(nm, nc) && !vis[nm][nc][nb]) {
                vis[nm][nc][nb] = true;
                vector<State> newPath = cur.path;
                newPath.push_back({nm, nc, nb});
                q.push({nm, nc, nb, newPath});
            }
        }
    }

    cout << "No solution found.\n";
    return 0;
}