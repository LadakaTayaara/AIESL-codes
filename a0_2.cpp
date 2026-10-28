/*
 * Problem: Water Jug Problem (Assignment 0.2)
 * Algorithm: Depth-First Search (DFS) with Backtracking
 *
 * Rules:
 * - Two jugs: Jug A with capacity 4 Liters, Jug B with capacity 3 Liters.
 * - Neither jug has markings.
 * - Goal: Measure exactly 2 Liters in Jug A (a == 2).
 * - State representation: (a, b)
 *     a: Current water in 4L jug (0 to 4)
 *     b: Current water in 3L jug (0 to 3)
 *
 * 6 Allowed Operations:
 * 1. Fill Jug A: (4, b)
 * 2. Fill Jug B: (a, 3)
 * 3. Empty Jug A: (0, b)
 * 4. Empty Jug B: (a, 0)
 * 5. Pour B into A until A is full or B is empty:
 *      a' = a + min(b, 4 - a), b' = b - min(b, 4 - a)
 * 6. Pour A into B until B is full or A is empty:
 *      a' = a - min(a, 3 - b), b' = b + min(a, 3 - b)
 */

#include <iostream>
#include <vector>
using namespace std;

// vis[a][b]: Tracks visited states (a in [0..4], b in [0..3]) to prevent infinite cycles
bool vis[5][4];

// Stores the sequence of (a, b) states from start to goal
vector<string> path;

// Recursive DFS to find a path from (0, 0) to a state where a == 2
bool dfs(int a, int b) {
    // If state has already been explored in this branch, backtrack
    if (vis[a][b]) return false;

    // Mark current state as visited and append to solution path
    vis[a][b] = 1;
    path.push_back("(" + to_string(a) + "," + to_string(b) + ")");

    // Goal condition: Exactly 2 liters in the 4L jug
    if (a == 2) return true;

    // Generate the 6 possible next states:
    int moves[][2] = {
        {4, b},                                 // 1. Fill 4L Jug A completely
        {a, 3},                                 // 2. Fill 3L Jug B completely
        {0, b},                                 // 3. Empty Jug A completely
        {a, 0},                                 // 4. Empty Jug B completely
        {a + min(b, 4 - a), b - min(b, 4 - a)}, // 5. Pour Jug B -> Jug A until A full or B empty
        {a - min(a, 3 - b), b + min(a, 3 - b)}  // 6. Pour Jug A -> Jug B until B full or A empty
    };

    // Explore each move recursively
    for (auto &m : moves)
        if (dfs(m[0], m[1])) return true;

    // Backtrack: remove current state if none of the moves led to goal
    path.pop_back();
    return false;
}

int main() {
    // Start with both jugs empty: (0, 0)
    if (dfs(0, 0)) {
        for (string s : path) cout << s << " -> ";
        cout << "Goal!\n";
    }
}