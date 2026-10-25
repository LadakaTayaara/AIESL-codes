#include <iostream>
#include <vector>
using namespace std;

string w1, w2, w3;
vector<char> ch;
int d[128];
bool used[10];

long long val(string s) {
    long long v = 0;
    for (char c : s) v = v * 10 + d[c];
    return v;
}

bool solve(int i) {
    if (i == ch.size())
        return d[w1[0]] && d[w2[0]] && d[w3[0]] && val(w1) + val(w2) == val(w3);

    for (int dig = 0; dig < 10; dig++) {
        if (!used[dig]) {
            used[dig] = 1; d[ch[i]] = dig;
            if (solve(i + 1)) return true;
            used[dig] = 0;
        }
    }
    return false;
}

int main() {
    if (!(cin >> w1 >> w2 >> w3)) return 0;
    bool seen[128] = {0};
    for (char c : w1 + w2 + w3)
        if (!seen[c]) { seen[c] = 1; ch.push_back(c); }

    if (solve(0)) {
        for (char c : ch) cout << c << "=" << d[c] << " ";
        cout << "\n" << val(w1) << " + " << val(w2) << " = " << val(w3) << "\n";
    }
}
