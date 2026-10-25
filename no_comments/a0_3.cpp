#include <iostream>
using namespace std;

void hanoi(int n, char from, char to, char aux) {
    if (!n) return;
    hanoi(n - 1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << "\n";
    hanoi(n - 1, aux, to, from);
}

int main() {
    int n;
    cout << "Enter disks: ";
    cin >> n;
    hanoi(n, 'A', 'C', 'B');
}
