#include <iostream>

using namespace std;

int stepCount = 0;

void solveHanoi(int n, char from, char to, char aux) {
    if (n == 0) return;
    solveHanoi(n - 1, from, aux, to);
    cout << "Step " << ++stepCount << ": Move disk " << n 
         << " from rod " << from << " to rod " << to << "\n";
    solveHanoi(n - 1, aux, to, from);
}

int main() {
    int n;
    cout << "Enter the number of disks for Tower of Hanoi: ";
    if (!(cin >> n)) return 0;

    cout << "\n--- State Space Moves (DFS) ---\n";
    solveHanoi(n, 'A', 'C', 'B');

    return 0;
}
