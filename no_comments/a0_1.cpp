#include <iostream>
#include <vector>
using namespace std;

bool vis[4][4][2];
int moves[][2] = {{1,0}, {2,0}, {0,1}, {0,2}, {1,1}};
vector<string> path;

bool ok(int m, int c) {
    return m >= 0 && c >= 0 && m <= 3 && c <= 3 &&
           (!m || m >= c) && (m == 3 || 3 - m >= 3 - c);
}

bool dfs(int m, int c, int b) {
    if (!ok(m, c) || vis[m][c][b]) return false;
    vis[m][c][b] = 1;
    path.push_back("(" + to_string(m) + "," + to_string(c) + "," + to_string(b) + ")");
    if (!m && !c && !b) return true;

    for (auto &v : moves)
        if (dfs(b ? m - v[0] : m + v[0], b ? c - v[1] : c + v[1], 1 - b)) return true;

    path.pop_back();
    return false;
}

int main() {
    if (dfs(3, 3, 1)) {
        for (string s : path) cout << s << " -> ";
        cout << "Goal!\n";
    }
}
