#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct State {
    int j1, j2;
    vector<pair<string, pair<int, int>>> path;
};

int main() {
    int max1 = 4, max2 = 3, target = 2;
    queue<State> q;
    bool vis[5][4] = {false};

    q.push({0, 0, {{"Initial State", {0, 0}}}});
    vis[0][0] = true;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.j1 == target) {
            cout << "\n--- State Space Search Path ---\n";
            cout << "Format: (4L Jug, 3L Jug) - Rule Applied\n";
            for (auto &step : cur.path) {
                cout << "State (" << step.second.first << ", " << step.second.second << ") : " 
                     << step.first << "\n";
            }
            return 0;
        }

        int j1 = cur.j1, j2 = cur.j2;

        vector<pair<string, pair<int, int>>> nextMoves = {
            {"Fill 4L Jug",   {max1, j2}},
            {"Fill 3L Jug",   {j1, max2}},
            {"Empty 4L Jug",  {0, j2}},
            {"Empty 3L Jug",  {j1, 0}},
            {"Pour 3L -> 4L", {j1 + min(j2, max1 - j1), j2 - min(j2, max1 - j1)}},
            {"Pour 4L -> 3L", {j1 - min(j1, max2 - j2), j2 + min(j1, max2 - j2)}}
        };

        for (auto &mv : nextMoves) {
            int nj1 = mv.second.first, nj2 = mv.second.second;
            if (!vis[nj1][nj2]) {
                vis[nj1][nj2] = true;
                vector<pair<string, pair<int, int>>> newPath = cur.path;
                newPath.push_back(mv);
                q.push({nj1, nj2, newPath});
            }
        }
    }

    cout << "No solution found.\n";
    return 0;
}
