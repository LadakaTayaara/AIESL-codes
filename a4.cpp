#include <iostream>
using namespace std;

char b[9];

int check() {
    int w[][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for (auto &l : w)
        if (b[l[0]] != ' ' && b[l[0]] == b[l[1]] && b[l[1]] == b[l[2]])
            return b[l[0]] == 'O' ? 10 : -10;
    return 0;
}

int minimax(bool isAI) {
    int score = check();
    if (score) return score;
    int best = isAI ? -100 : 100;
    bool full = true;
    for (int i = 0; i < 9; i++) {
        if (b[i] == ' ') {
            full = false;
            b[i] = isAI ? 'O' : 'X';
            int v = minimax(!isAI);
            b[i] = ' ';
            best = isAI ? max(best, v) : min(best, v);
        }
    }
    return full ? 0 : best;
}

int main() {
    for (int i = 0; i < 9; i++) b[i] = ' ';
    int m;
    while (!check() && cin >> m) {
        if (m < 1 || m > 9 || b[m - 1] != ' ') continue;
        b[m - 1] = 'X';

        int best = -100, move = -1;
        for (int i = 0; i < 9; i++) {
            if (b[i] == ' ') {
                b[i] = 'O';
                int v = minimax(false);
                b[i] = ' ';
                if (v > best) { best = v; move = i; }
            }
        }
        if (move != -1) b[move] = 'O';

        for (int i = 0; i < 9; i++)
            cout << b[i] << (i % 3 == 2 ? "\n" : " ");

        if (check() == 10) { cout << "AI wins!\n"; break; }
        if (check() == -10) { cout << "You win!\n"; break; }
    }
}
