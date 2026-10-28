/*
 * Problem: Missionaries and Cannibals (Assignment 0.1)
 * Algorithm: Depth-First Search (DFS) with Backtracking
 *
 * Rules:
 * - 3 Missionaries (M) and 3 Cannibals (C) need to cross a river using a boat.
 * - Boat holds at most 2 people and cannot cross empty.
 * - If cannibals outnumber missionaries on either bank, the missionaries are eaten.
 * - State representation: (m, c, b)
 *     m: Number of missionaries on the left bank (0 to 3)
 *     c: Number of cannibals on the left bank (0 to 3)
 *     b: Boat location (1 = Left bank, 0 = Right bank)
 */

#include <iostream>
#include <vector>
using namespace std;

// vis[m][c][b]: Tracks visited states to prevent infinite loops in DFS
bool vis[4][4][2];

// Possible boat loads: {missionaries, cannibals} crossing the river
// Max boat capacity is 2: {1M, 0C}, {2M, 0C}, {0M, 1C}, {0M, 2C}, {1M, 1C}
int moves[][2] = {{1,0}, {2,0}, {0,1}, {0,2}, {1,1}};

// Stores the sequence of valid states from start to goal
vector<string> path;

// Validation function: checks if a bank state is safe
bool ok(int m, int c) {
    return m >= 0 && c >= 0 && m <= 3 && c <= 3 &&   // Counts must stay between 0 and 3
           (!m || m >= c) &&                         // Left bank: safe if no missionaries OR M >= C
           (m == 3 || 3 - m >= 3 - c);               // Right bank: safe if no missionaries (m==3) OR (3-m) >= (3-c)
}

// Recursive DFS to find a path from initial state (3,3,1) to goal state (0,0,0)
bool dfs(int m, int c, int b) {
    // If state violates safety rules or was already visited, prune this branch
    if (!ok(m, c) || vis[m][c][b]) return false;

    // Mark current state as visited and record in path
    vis[m][c][b] = 1;
    path.push_back("(" + to_string(m) + "," + to_string(c) + "," + to_string(b) + ")");

    // Goal reached: All 3 missionaries, 3 cannibals, and boat are on the right bank (0,0,0)
    if (!m && !c && !b) return true;

    // Try all valid boat passenger combinations
    for (auto &v : moves) {
        // If boat is on left (b=1), passengers leave left bank (-v)
        // If boat is on right (b=0), passengers return to left bank (+v)
        int next_m = b ? m - v[0] : m + v[0];
        int next_c = b ? c - v[1] : c + v[1];
        int next_b = 1 - b; // Toggle boat position

        if (dfs(next_m, next_c, next_b)) return true;
    }

    // Backtrack: remove current state if it didn't lead to goal
    path.pop_back();
    return false;
}

int main() {
    // Start with all 3 missionaries, 3 cannibals, and boat on the left bank (3, 3, 1)
    if (dfs(3, 3, 1)) {
        for (string s : path) cout << s << " -> ";
        cout << "Goal!\n";
    }
}