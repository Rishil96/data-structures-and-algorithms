#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


// 1. Number of Provinces
void fcnDFS(int src, vector<vector<int>> &isConnected, unordered_map<int, bool>& vis) {
    // Mark src as visited
    vis[src] = true;

    // Loop through the city row and visit all cities connected to it
    for (int i=0; i<isConnected.size(); i++) {
        // Check 3 things
        // 1. We are not visited the same city again
        // 2. The city is connected as per isConnected vector
        // 3. The city is not yet visited
        if (i != src && isConnected[src][i] == 1 && !vis[i]) {
            fcnDFS(i, isConnected, vis);
        }
    }
}

int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    int provinces = 0;
    unordered_map<int, bool> isVis;

    // Loop through each city and call DFS to traverse to its connected cities
    for (int city=0; city<n; city++) {
        if (!isVis[city]) {
            provinces++;
            // DFS will only be called for unvisited cities so every unvisited city will be part of a new province
            fcnDFS(city, isConnected, isVis);
        }
    }

    return provinces;
}


// 2.


// 3.


// 4.


// 5.


int main() {
    

    return 0;
}