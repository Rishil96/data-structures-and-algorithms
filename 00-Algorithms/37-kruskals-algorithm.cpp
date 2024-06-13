#include <iostream>
using namespace std;

// Comparator to sort edge DS
static bool mycmp(vector<int> &a, vector<int>& b) {
    return a[2] < b[2];
}	

// Helper function to find parent of node recursively
int findParent(vector<int>& parent, int node) {
    if (parent[node] == node) return node;
    return parent[node] = findParent(parent, parent[node]);     // Path compression
}

// Helper function to merge 2 disconnected components
void unionSet(int u, int v, vector<int>& parent, vector<int>& rank) {
    u = findParent(parent, u);
    v = findParent(parent, v);
    
    if (rank[u] < rank[v]) {
        parent[u] = v;
        rank[v]++;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}


//Function to find sum of weights of edges of the Minimum Spanning Tree.
int spanningTree(int V, vector<vector<int>> adj[])
{
    // Init variables
    vector<int> parent(V);
    vector<int> rank(V, 0);
    int ans = 0;
    
    // Make all nodes parent of themselves
    for (int u=0; u<V; u++) parent[u] = u;
    
    // Make the linear DS
    vector<vector<int>> edges;
    for (int u=0; u<V; u++) {
        for (auto edge: adj[u]) {
            int v = edge[0];
            int wt = edge[1];
            
            edges.push_back({u, v, wt});
        }
    }
    
    // Sort the linear DS edges
    sort(edges.begin(), edges.end(), mycmp);
    
    // Start Kruskal's algorithm
    for (auto edge: edges) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];
    
        u = findParent(parent, u);
        v = findParent(parent, v);
        
        if (u != v) {
            unionSet(u, v, parent, rank);
            ans += w;
        }
    }
    
    return ans;
}

int main() {

    

    return 0;
}