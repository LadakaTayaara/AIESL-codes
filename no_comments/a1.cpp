#include <iostream>
#include <queue>
#include <map>
#include <vector>

using namespace std;

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

int main() {
    string start = "123406758", goal = "123456780";
    priority_queue<pair<int, string>> pq;
    map<string, int> g;
    map<string, string> p;

    pq.push({-getH(start), start});
    g[start] = 0;

    while (!pq.empty()) {
        string cur = pq.top().second;
        pq.pop();

        if (cur == goal) {
            cout << "Solved in " << g[cur] << " moves!\n\n";
            vector<string> path;
            for (string s = goal; s != ""; s = p[s]) path.push_back(s);
            for (int i = path.size() - 1; i >= 0; i--) print(path[i]);
            return 0;
        }

        int z = cur.find('0');
        for (int m : {-3, 3, -1, 1}) {
            int nz = z + m;
            if (nz < 0 || nz > 8 || (m == -1 && z % 3 == 0) || (m == 1 && z % 3 == 2)) continue;
            string nxt = cur;
            swap(nxt[z], nxt[nz]);
            if (!g.count(nxt) || g[cur] + 1 < g[nxt]) {
                g[nxt] = g[cur] + 1;
                p[nxt] = cur;
                pq.push({-(g[nxt] + getH(nxt)), nxt});
            }
        }
    }
}
