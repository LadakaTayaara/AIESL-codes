#include <iostream>
#include <vector>

using namespace std;

string goal = "123456780";
vector<string> path;

int getH(string s) {
    int h = 0;
    for (int i = 0; i < 9; i++)
        if (s[i] != '0')
            h += abs(i / 3 - (s[i] - '1') / 3) + abs(i % 3 - (s[i] - '1') % 3);
    return h;
}

void print(string s) {
    for (int i = 0; i < 9; i++)
        cout << (s[i] == '0' ? '_' : s[i]) << (i % 3 == 2 ? "\n" : " ");
    cout << "------\n";
}

bool dfs(string cur, int g, int limit) {
    if (g + getH(cur) > limit) return false;
    path.push_back(cur);
    if (cur == goal) return true;

    int z = cur.find('0');
    for (int m : {-3, 3, -1, 1}) {
        int nz = z + m;
        if (nz < 0 || nz > 8 || (m == -1 && z % 3 == 0) || (m == 1 && z % 3 == 2)) continue;
        string nxt = cur;
        swap(nxt[z], nxt[nz]);
        if (path.size() >= 2 && nxt == path[path.size() - 2]) continue;

        if (dfs(nxt, g + 1, limit)) return true;
    }
    path.pop_back();
    return false;
}

int main() {
    string start = "123406758";
    int limit = getH(start);
    while (!dfs(start, 0, limit)) limit++;

    cout << "Solved in " << path.size() - 1 << " moves!\n\n";
    for (string s : path) print(s);
}
