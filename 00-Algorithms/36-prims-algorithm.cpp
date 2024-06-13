#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

// Prims Algorithm
int getMin(vector<int>& key, vector<bool>& mst) {
	    
    int value = INT_MAX;
    int index = -1;
    
    for (int i=0; i<key.size(); i++) {
        if (key[i] < value && !mst[i]) {
            value = key[i];
            index = i;
        }
    }
    
    return index;
}

//Function to find sum of weights of edges of the Minimum Spanning Tree.
int spanningTree(int V, vector<vector<int>> adj[])
{
    // code here
    
    // Step 1: Initialize variables
    vector<int> key(V, INT_MAX);
    vector<bool> mst(V, false);
    vector<int> parent(V, -1);
    
    key[0] = 0;
    
    // Algorithm runs till all nodes are added in MST
    while (true) {
        
        // Step 2: Get minimum value node that is not yet added in MST
        int u = getMin(key, mst);
        
        // Check if all nodes are already added in MST
        if (u == -1) break;
        
        // Add u in MST
        mst[u] = true;
        
        // Step 3: Process all adjacent nodes of u
        for (auto edge: adj[u]) {
            int v = edge[0];
            int wt = edge[1];
            
            // If v is not added in MST and wt is less than the key value of v set key and parent value
            if (mst[v] == false && wt < key[v]) {
                key[v] = wt;
                parent[v] = u;
            }
        }
        
    }
    
    int sum = 0;
    for (auto k : key) sum += k;
    
    return sum;
}

int main() {

    

    return 0;
}