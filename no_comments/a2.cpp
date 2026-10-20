#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int calcCost(const vector<int> &tour, const vector<vector<int>> &cost) {
    int total = 0, n = tour.size();
    for (int i = 0; i < n; i++) {
        total += cost[tour[i]][tour[(i + 1) % n]];
    }
    return total;
}

int main() {
    srand(time(0));

    int n;
    cout << "Enter the number of variables (cities):\n";
    if (!(cin >> n)) return 0;

    vector<vector<int>> cost(n, vector<int>(n));
    cout << "Enter the data for adjacency matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    vector<int> tour(n);
    for (int i = 0; i < n; i++) tour[i] = i;

    int bestCost = calcCost(tour, cost);

    for (int k = 0; k < 10000; k++) {
        int a = 1 + rand() % (n - 1);
        int b = 1 + rand() % (n - 1);
        if (a == b) continue;

        swap(tour[a], tour[b]);
        int newCost = calcCost(tour, cost);

        if (newCost < bestCost) {
            bestCost = newCost;
        } else {
            swap(tour[a], tour[b]);
        }
    }

    cout << "\nBest Cost: " << bestCost << "\nBest Tour: ";
    for (int city : tour) cout << city << " -> ";
    cout << tour[0] << "\n";

    return 0;
}
