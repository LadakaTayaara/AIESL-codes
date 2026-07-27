#include <iostream>

using namespace std;

class TowerOfHanoi {
private:
    int stepCount = 0;

public:
    // Recursive function representing DFS through the state space
    void solve(int n, char source, char destination, char auxiliary) {
        // Base case: Only one disk to move
        if (n == 1) {
            stepCount++;
            cout << "Step " << stepCount << ": Move disk 1 from rod " 
                 << source << " to rod " << destination << endl;
            return;
        }
        
        // Step 1: Move n-1 disks from Source to Auxiliary (using Destination as temp)
        solve(n - 1, source, auxiliary, destination);
        
        // Step 2: Move the nth (largest) disk from Source to Destination
        stepCount++;
        cout << "Step " << stepCount << ": Move disk " << n 
             << " from rod " << source << " to rod " << destination << endl;
        
        // Step 3: Move the n-1 disks from Auxiliary to Destination (using Source as temp)
        solve(n - 1, auxiliary, destination, source);
    }
};

int main() {
    int numDisks;
    cout << "Enter the number of disks for Tower of Hanoi: ";
    cin >> numDisks;
    
    TowerOfHanoi toh;
    cout << "\n--- State Space Moves (DFS) ---" << endl;
    toh.solve(numDisks, 'A', 'C', 'B'); // A = Source, C = Destination, B = Auxiliary
    
    return 0;
}