/*
 * Problem: 8-Puzzle Problem (Assignment 1)
 * Algorithm: Recursive Iterative Deepening A* (IDA*)
 *
 * Board Representation:
 * - 3x3 grid stored as a 9-character string, with '0' as the blank tile.
 * - Indices:
 *     0 1 2
 *     3 4 5
 *     6 7 8
 * - Coordinate mapping for index i: row = i / 3, col = i % 3
 * - Goal State: "123456780" (tiles 1 to 8 sorted, blank at end)
 *
 * Heuristic Function (h):
 * - Manhattan Distance: Sum of horizontal and vertical distances of each tile
 *   from its target position. Admissible (never overestimates).
 *
 * Algorithm Strategy (IDA*):
 * - Depth-bounded recursive search where f(n) = g(n) + h(n).
 * - g(n) = moves made so far (depth).
 * - h(n) = estimated moves left (Manhattan distance).
 * - Branches where g + h > limit are pruned immediately.
 * - In main(), limit starts at h(start) and increments until a solution is found.
 * - Memory Complexity: O(d) linear stack space instead of exponential open list.
 */

#include <iostream>
#include <vector>

using namespace std;

string goal = "123456780"; // Target solved state
vector<string> path;        // Stores the path of board states from start to goal

// Computes Manhattan Distance heuristic for the current board state
int getH(string s) {
    int h = 0;
    for (int i = 0; i < 9; i++) {
        if (s[i] != '0') {
            // Target index for tile s[i]: '1' -> 0, '2' -> 1, ..., '8' -> 7
            int target = s[i] - '1';
            // Manhattan distance = |cur_row - target_row| + |cur_col - target_col|
            h += abs(i / 3 - target / 3) + abs(i % 3 - target % 3);
        }
    }
    return h;
}

// Pretty prints the 9-character string as a 3x3 board ('_' represents blank)
void print(string s) {
    for (int i = 0; i < 9; i++)
        cout << (s[i] == '0' ? '_' : s[i]) << (i % 3 == 2 ? "\n" : " ");
    cout << "------\n";
}

// Recursive depth-first search bounded by cost threshold 'limit'
bool dfs(string cur, int g, int limit) {
    // Prune: if actual moves (g) + estimated remaining (h) exceeds budget, backtrack
    if (g + getH(cur) > limit) return false;

    path.push_back(cur);
    if (cur == goal) return true; // Solution found!

    int z = cur.find('0'); // Locate the empty tile

    // 4 possible sliding directions for the blank tile:
    // -3: Up, +3: Down, -1: Left, +1: Right
    for (int m : {-3, 3, -1, 1}) {
        int nz = z + m;

        // Boundary checks:
        // 1. Off the top or bottom board edges
        // 2. Off the left edge (cannot move left if blank is in col 0: z % 3 == 0)
        // 3. Off the right edge (cannot move right if blank is in col 2: z % 3 == 2)
        if (nz < 0 || nz > 8 || (m == -1 && z % 3 == 0) || (m == 1 && z % 3 == 2))
            continue;

        string nxt = cur;
        swap(nxt[z], nxt[nz]); // Perform move by sliding neighbor tile into blank

        // Cycle check: Avoid immediately undoing the previous move (prevents 2-step loops)
        if (path.size() >= 2 && nxt == path[path.size() - 2]) continue;

        // Recurse to explore deeper with g + 1
        if (dfs(nxt, g + 1, limit)) return true;
    }

    // Backtrack: remove current state if no child reached the goal within limit
    path.pop_back();
    return false;
}

int main() {
    string start = "123406758"; // Initial puzzle state

    // Iterative Deepening: Start limit at h(start), increment until goal is reached
    int limit = getH(start);
    while (!dfs(start, 0, limit)) limit++;

    cout << "Solved in " << path.size() - 1 << " moves!\n\n";
    for (string s : path) print(s);
}