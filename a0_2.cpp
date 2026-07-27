#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// Structure to represent (Jug1, Jug2) states
struct JugState {
    int j1, j2;
    string ruleApplied;
    JugState* parent;
};

class WaterJug {
    int max1 = 4; // Capacity of Jug 1
    int max2 = 3; // Capacity of Jug 2
    int target = 2; // Target volume in Jug 1

public:
    void printPath(JugState* goal) {
        vector<JugState*> path;
        for (JugState* cur = goal; cur != nullptr; cur = cur->parent) {
            path.push_back(cur);
        }
        
        cout << "\n--- State Space Search Path ---" << endl;
        cout << "Format: (4L Jug, 3L Jug) - Rule Applied\n";
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << "State (" << path[i]->j1 << ", " << path[i]->j2 << ") : " 
                 << path[i]->ruleApplied << endl;
        }
    }

    void solve() {
        queue<JugState*> q;
        bool visited[5][4] = {false}; // Max states are 0-4 for j1, 0-3 for j2

        JugState* initial = new JugState{0, 0, "Initial State", nullptr};
        q.push(initial);
        visited[0][0] = true;

        while (!q.empty()) {
            JugState* curr = q.front();
            q.pop();

            // Goal State condition (2 Liters in the 4L jug)
            if (curr->j1 == target) {
                printPath(curr);
                return;
            }

            // Define all production rules (state transitions)
            // 1. Fill 4L Jug
            if (curr->j1 < max1 && !visited[max1][curr->j2]) {
                visited[max1][curr->j2] = true;
                q.push(new JugState{max1, curr->j2, "Fill 4L Jug", curr});
            }
            // 2. Fill 3L Jug
            if (curr->j2 < max2 && !visited[curr->j1][max2]) {
                visited[curr->j1][max2] = true;
                q.push(new JugState{curr->j1, max2, "Fill 3L Jug", curr});
            }
            // 3. Empty 4L Jug
            if (curr->j1 > 0 && !visited[0][curr->j2]) {
                visited[0][curr->j2] = true;
                q.push(new JugState{0, curr->j2, "Empty 4L Jug", curr});
            }
            // 4. Empty 3L Jug
            if (curr->j2 > 0 && !visited[curr->j1][0]) {
                visited[curr->j1][0] = true;
                q.push(new JugState{curr->j1, 0, "Empty 3L Jug", curr});
            }
            // 5. Pour from 3L to 4L
            if (curr->j2 > 0 && curr->j1 < max1) {
                int amount = min(curr->j2, max1 - curr->j1);
                int next1 = curr->j1 + amount;
                int next2 = curr->j2 - amount;
                if (!visited[next1][next2]) {
                    visited[next1][next2] = true;
                    q.push(new JugState{next1, next2, "Pour 3L -> 4L", curr});
                }
            }
            // 6. Pour from 4L to 3L
            if (curr->j1 > 0 && curr->j2 < max2) {
                int amount = min(curr->j1, max2 - curr->j2);
                int next1 = curr->j1 - amount;
                int next2 = curr->j2 + amount;
                if (!visited[next1][next2]) {
                    visited[next1][next2] = true;
                    q.push(new JugState{next1, next2, "Pour 4L -> 3L", curr});
                }
            }
        }
    }
};

int main() {
    cout << "Starting Water Jug Problem...\n";
    WaterJug wj;
    wj.solve();
    return 0;
}