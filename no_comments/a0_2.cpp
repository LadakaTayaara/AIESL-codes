#include <iostream>
#include <vector>
using namespace std;

bool vis[5][4];
vector<string> path;

bool dfs(int a, int b) {
    if (vis[a][b]) return false;
    vis[a][b] = 1;
    path.push_back("(" + to_string(a) + "," + to_string(b) + ")");
    if (a == 2) return true;

    int moves[][2] = {
        {4, b}, {a, 3}, {0, b}, {a, 0},
        {a + min(b, 4 - a), b - min(b, 4 - a)},
        {a - min(a, 3 - b), b + min(a, 3 - b)}
    };

    for (auto &m : moves)
        if (dfs(m[0], m[1])) return true;

    path.pop_back();
    return false;
}

int main() {
    if (dfs(0, 0)) {
        for (string s : path) cout << s << " -> ";
        cout << "Goal!\n";
    }
}
