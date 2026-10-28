/*
 * Problem: Traveling Salesperson Problem - TSP (Assignment 2)
 * Algorithm: Hill Climbing / Local Search (Iterated 2-Opt Random Swap)
 *
 * Problem Description:
 * - Given n cities and an n x n cost adjacency matrix c[i][j].
 * - Find a closed tour visiting every city exactly once and returning to the start city
 *   that minimizes the total travel cost.
 * - NP-Hard problem: Exact search takes O(n!), so Hill Climbing / Local Search is used.
 *
 * Algorithm Strategy:
 * 1. Start with an initial tour: 0 -> 1 -> 2 -> ... -> (n - 1) -> 0.
 * 2. In each iteration (1000 random steps):
 *    - Pick two random intermediate cities (excluding the fixed origin city 0).
 *    - Swap them in the tour.
 *    - If new tour cost is strictly better (lower), keep the swap.
 *    - Otherwise, reject and swap back (Hill Climbing acceptance criterion).
 */

#include <iostream>
using namespace std;

int c[10][10]; // Distance/Cost matrix between cities (max 10 cities)
int t[10];      // Tour array: stores the sequence of visited cities
int n;          // Number of cities

// Calculates the total cost of the current closed tour t[0] -> t[1] -> ... -> t[n-1] -> t[0]
int cost() {
    int s = 0;
    for (int i = 0; i < n; i++)
        s += c[t[i]][t[(i + 1) % n]]; // Add cost from city t[i] to next city t[(i+1)%n]
    return s;
}

int main() {
    cout << "Enter n: ";
    if (!(cin >> n)) return 0;

    cout << "Enter matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> c[i][j];

    // Initialize initial tour: 0, 1, 2, ..., n-1
    for (int i = 0; i < n; i++) t[i] = i;
    int best = cost(); // Cost of initial tour

    // Hill Climbing iterations (1000 random neighborhood perturbations)
    for (int k = 0; k < 1000; k++) {
        // Pick two random city indices between 1 and n-1 (keep city 0 fixed as start/end)
        int a = 1 + rand() % (n - 1);
        int b = 1 + rand() % (n - 1);

        // Perturb: swap the two cities in the tour
        swap(t[a], t[b]);
        int cur = cost();

        // If new tour improves cost, accept the new state
        if (cur < best) {
            best = cur;
        } else {
            // Hill climbing rejects worse moves: undo the swap
            swap(t[a], t[b]);
        }
    }

    // Output optimal/best found tour and total cost
    cout << "Best Cost: " << best << "\nTour: ";
    for (int i = 0; i <= n; i++) cout << t[i % n] << " ";
    cout << "\n";
}