/*
 * Problem: Tower of Hanoi (Assignment 0.3)
 * Algorithm: Classic Divide-and-Conquer Recursion
 *
 * Rules:
 * - 3 Pegs: Source ('A'), Destination ('C'), Auxiliary ('B')
 * - Move all n disks from Peg A to Peg C using Peg B as temporary storage.
 * - Only 1 disk can be moved at a time.
 * - A larger disk can NEVER be placed on top of a smaller disk.
 *
 * Recurrence Relation: T(n) = 2*T(n-1) + 1 => Total moves = 2^n - 1
 * Time Complexity: O(2^n)
 * Space Complexity: O(n) call stack depth
 */

#include <iostream>
using namespace std;

/*
 * Recursive function to move n disks:
 * - n: Number of disks to move
 * - from: Source peg
 * - to: Target destination peg
 * - aux: Helper / auxiliary peg
 */
void hanoi(int n, char from, char to, char aux) {
    // Base Case: If there are 0 disks left to move, return
    if (!n) return;

    // Step 1: Recursively move the top (n - 1) disks from 'from' to 'aux', using 'to' as helper
    hanoi(n - 1, from, aux, to);

    // Step 2: Move the remaining largest disk (n) directly from 'from' to 'to'
    cout << "Move disk " << n << " from " << from << " to " << to << "\n";

    // Step 3: Recursively move the (n - 1) disks from 'aux' to 'to', using 'from' as helper
    hanoi(n - 1, aux, to, from);
}

int main() {
    int n;
    cout << "Enter disks: ";
    cin >> n;

    // Move n disks from Peg A to Peg C using Peg B as auxiliary
    hanoi(n, 'A', 'C', 'B');
}