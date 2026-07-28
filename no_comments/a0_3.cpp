#include <iostream>

using namespace std;

class TowerOfHanoi {
private:
    int stepCount = 0;

public:
    void solve(int n, char source, char destination, char auxiliary) {
        if (n == 1) {
            stepCount++;
            cout << "Step " << stepCount << ": Move disk 1 from rod " 
                 << source << " to rod " << destination << endl;
            return;
        }
        
        solve(n - 1, source, auxiliary, destination);
        
        stepCount++;
        cout << "Step " << stepCount << ": Move disk " << n 
             << " from rod " << source << " to rod " << destination << endl;
        
        solve(n - 1, auxiliary, destination, source);
    }
};

int main() {
    int numDisks;
    cout << "Enter the number of disks for Tower of Hanoi: ";
    cin >> numDisks;
    
    TowerOfHanoi toh;
    cout << "\n--- State Space Moves (DFS) ---" << endl;
    toh.solve(numDisks, 'A', 'C', 'B');
    
    return 0;
}
