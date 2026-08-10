#include <bits/stdc++.h>
using namespace std;

int calcCost(vector<int> &tour, vector<vector<int>> &cost) {
    int n = tour.size(), total = 0;
    for (int i = 0; i < n - 1; i++) total += cost[tour[i]][tour[i+1]];
    return total + cost[tour[n-1]][tour[0]];
}

int tspHillClimb(vector<vector<int>> &cost, int maxIter=10000) {
    int n = cost.size();
    vector<int> tour(n); iota(tour.begin(), tour.end(), 0);
    random_shuffle(tour.begin()+1, tour.end()); // random start
    int best = calcCost(tour, cost);

    for (int k = 0; k < maxIter; k++) {
        vector<int> newTour = tour;
        int a = 1 + rand() % (n-1), b = 1 + rand() % (n-1); // avoid swapping start
        swap(newTour[a], newTour[b]);
        int newCost = calcCost(newTour, cost);
        if (newCost < best) { tour = newTour; best = newCost; }
    }
    return best;
}

int main() {
    srand(time(0));

    cout<<"Enter the number of variable\n";
    int n;
    cin>>n;
    vector<vector<int>> cost(n,vector<int>(n));

    cout<<"Enter the data for adjacency matrix\n";

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>cost[i][j];
        }
    }

    cout << "\ncost :" <<  tspHillClimb(cost) << endl;
}