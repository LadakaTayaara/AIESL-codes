#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State {
    int m, c, b;
    vector<State> path;
};

bool isValid(int m, int c) {
    if (m < 0 || c < 0 || m > 3 || c > 3) return false;
    if (m > 0 && m < c) return false;
    if (3 - m > 0 && (3 - m) < (3 - c)) return false;
    return true;
}

int main() {
    queue<State> q;
    bool vis[4][4][2] = {false};

    q.push({3, 3, 1, {{3, 3, 1}}});
    vis[3][3][1] = true;

    int moves[5][2] = {{1, 0}, {2, 0}, {0, 1}, {0, 2}, {1, 1}};

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

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
