#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

string word1, word2, resultWord;
vector<char> uniqueChars;
map<char, int> charToDigit;
bool digitUsed[10] = {false};

long long getWordValue(const string& word) {
    long long num = 0;
    for (char c : word) {
        num = num * 10 + charToDigit[c];
    }
    return num;
}

bool solveCSP(int index) {
    if (index == uniqueChars.size()) {
        if (charToDigit[word1[0]] == 0 || charToDigit[word2[0]] == 0 || charToDigit[resultWord[0]] == 0) {
            return false;
        }

        long long val1 = getWordValue(word1);
        long long val2 = getWordValue(word2);
        long long valResult = getWordValue(resultWord);

        if (val1 + val2 == valResult) {
            cout << "\n=== Solution Found! ===" << endl;
            cout << "Letter Assignments:" << endl;
            for (auto pair : charToDigit) {
                cout << pair.first << " = " << pair.second << endl;
            }
            cout << "\nEquation Verification:" << endl;
            cout << "  " << word1 << " (" << val1 << ")" << endl;
            cout << "+ " << word2 << " (" << val2 << ")" << endl;
            cout << "-----------------" << endl;
            cout << "= " << resultWord << " (" << valResult << ")" << endl;
            return true;
        }
        return false;
    }

    char currentChar = uniqueChars[index];
    for (int digit = 0; digit <= 9; digit++) {
        if (!digitUsed[digit]) {
            charToDigit[currentChar] = digit;
            digitUsed[digit] = true;

            if (solveCSP(index + 1)) {
                return true;
            }

            digitUsed[digit] = false;
        }
    }

    return false;
}

void solve() {
    cout << "=== Cryptarithmetic CSP Solver ===" << endl;
    cout << "Enter Word 1: ";
    cin >> word1;
    cout << "Enter Word 2: ";
    cin >> word2;
    cout << "Enter Result Word: ";
    cin >> resultWord;

    uniqueChars.clear();
    charToDigit.clear();
    for (int i = 0; i < 10; i++) digitUsed[i] = false;

    set<char> charSet;
    for (char c : word1) charSet.insert(c);
    for (char c : word2) charSet.insert(c);
    for (char c : resultWord) charSet.insert(c);

    for (char c : charSet) {
        uniqueChars.push_back(c);
    }

    if (uniqueChars.size() > 10) {
        cout << "Error: More than 10 unique letters! Impossible to assign unique digits (0-9)." << endl;
        return;
    }

    cout << "\nSolving: " << word1 << " + " << word2 << " = " << resultWord << " ..." << endl;

    if (!solveCSP(0)) {
        cout << "No solution exists for this cryptarithmetic puzzle." << endl;
    }
}

int main() {
    solve();
    return 0;
}
