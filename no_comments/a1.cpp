#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>

using namespace std;

const vector<vector<int>> GOAL = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

struct Node {
    int f, g;
    vector<vector<int>> b;
    vector<vector<vector<int>>> path;

    bool operator>(const Node &o) const {
        return f > o.f;
    }
};

int getManhattan(const vector<vector<int>> &b) {
    int h = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int val = b[i][j];
            if (val != 0) {
                int target_r = (val - 1) / 3;
                int target_c = (val - 1) % 3;
                h += abs(i - target_r) + abs(j - target_c);
            }
        }
    }
    return h;
}

void printBoard(const vector<vector<int>> &b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == 0) cout << "_ ";
            else cout << b[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "------\n";
}

int main() {
    vector<vector<int>> start = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };

    cout << "8-Puzzle A* Algorithm Initialized.\n";
    cout << "Initial Board State:\n";
    printBoard(start);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<vector<vector<int>>> visited;

    int h = getManhattan(start);
    pq.push({h, 0, start, {start}});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.b == GOAL) {
            cout << "\nOptimal Path Found in " << cur.g << " moves:\n\n";
            for (int step = 0; step < cur.path.size(); step++) {
                cout << "Step " << step << ":\n";
                printBoard(cur.path[step]);
            }
            return 0;
        }

        if (visited.count(cur.b)) continue;
        visited.insert(cur.b);

        int zr = 0, zc = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (cur.b[i][j] == 0) { zr = i; zc = j; }

        for (int i = 0; i < 4; i++) {
            int nr = zr + dr[i], nc = zc + dc[i];
            if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
                auto nb = cur.b;
                swap(nb[zr][zc], nb[nr][nc]);

                if (!visited.count(nb)) {
                    int ng = cur.g + 1;
                    int nf = ng + getManhattan(nb);
                    auto newPath = cur.path;
                    newPath.push_back(nb);
                    pq.push({nf, ng, nb, newPath});
                }
            }
        }
    }

    cout << "No solution exists for this initial configuration.\n";
    return 0;
}
