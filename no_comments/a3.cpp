#include <iostream>
#include <vector>
#include <string>

using namespace std;

string w1, w2, w3;
vector<char> letters;
int digit[256];
bool used[10];

long long getVal(const string &s) {
    long long val = 0;
    for (char c : s) val = val * 10 + digit[c];
    return val;
}

bool solve(int idx) {
    if (idx == letters.size()) {
        if (digit[w1[0]] == 0 || digit[w2[0]] == 0 || digit[w3[0]] == 0) return false;
        return getVal(w1) + getVal(w2) == getVal(w3);
    }

    for (int d = 0; d <= 9; d++) {
        if (!used[d]) {
            used[d] = true;
            digit[letters[idx]] = d;

            if (solve(idx + 1)) return true;

            used[d] = false;
        }
    }
    return false;
}

int main() {
    cout << "=== Cryptarithmetic CSP Solver ===\n";
    cout << "Enter Word 1: ";
    cin >> w1;
    cout << "Enter Word 2: ";
    cin >> w2;
    cout << "Enter Result Word: ";
    cin >> w3;

    bool seen[256] = {false};
    for (char c : w1 + w2 + w3) {
        if (!seen[c]) {
            seen[c] = true;
            letters.push_back(c);
        }
    }

    if (letters.size() > 10) {
        cout << "Error: More than 10 unique letters! Cannot assign digits 0-9.\n";
        return 0;
    }

    cout << "\nSolving: " << w1 << " + " << w2 << " = " << w3 << " ...\n";

    if (solve(0)) {
        cout << "\n=== Solution Found! ===\nLetter Assignments:\n";
        for (char c : letters) cout << c << " = " << digit[c] << "\n";

        cout << "\nEquation Verification:\n";
        cout << "  " << w1 << " (" << getVal(w1) << ")\n";
        cout << "+ " << w2 << " (" << getVal(w2) << ")\n";
        cout << "-----------------\n";
        cout << "= " << w3 << " (" << getVal(w3) << ")\n";
    } else {
        cout << "No solution exists for this cryptarithmetic puzzle.\n";
    }

    return 0;
}
