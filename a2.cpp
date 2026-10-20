/*
 * Problem: Traveling Salesperson Problem (TSP) using Hill Climbing
 * Subject: AIES (SPPU)
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Calculate total tour cost returning to the start city
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

    // Initial tour: 0, 1, 2, ..., n-1
    vector<int> tour(n);
    for (int i = 0; i < n; i++) tour[i] = i;

    int bestCost = calcCost(tour, cost);

    // Hill Climbing: randomly swap two cities (excluding starting city 0)
    for (int k = 0; k < 10000; k++) {
        int a = 1 + rand() % (n - 1);
        int b = 1 + rand() % (n - 1);
        if (a == b) continue;

        swap(tour[a], tour[b]);
        int newCost = calcCost(tour, cost);

        if (newCost < bestCost) {
            bestCost = newCost; // Better neighbor found, accept move
        } else {
            swap(tour[a], tour[b]); // Undo swap
        }
    }

    cout << "\nBest Cost: " << bestCost << "\nBest Tour: ";
    for (int city : tour) cout << city << " -> ";
    cout << tour[0] << "\n";

    return 0;
}