#include <iostream>
using namespace std;

int c[10][10], t[10], n;

int cost() {
    int s = 0;
    for (int i = 0; i < n; i++) s += c[t[i]][t[(i + 1) % n]];
    return s;
}

int main() {
    cout << "Enter n: ";
    if (!(cin >> n)) return 0;
    cout << "Enter matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> c[i][j];

    for (int i = 0; i < n; i++) t[i] = i;
    int best = cost();

    for (int k = 0; k < 1000; k++) {
        int a = 1 + rand() % (n - 1), b = 1 + rand() % (n - 1);
        swap(t[a], t[b]);
        int cur = cost();
        if (cur < best) best = cur;
        else swap(t[a], t[b]);
    }

    cout << "Best Cost: " << best << "\nTour: ";
    for (int i = 0; i <= n; i++) cout << t[i % n] << " ";
    cout << "\n";
}
