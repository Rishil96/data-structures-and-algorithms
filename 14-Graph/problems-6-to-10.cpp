#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// 6. Course Schedule 2
vector<int> topologicalSort(unordered_map<int, list<int>> &adjList, int &numCourses) {
    vector<int> topoSort;
    // Step 1: Create Indegree of each node
    unordered_map<int, int> indegree;
    for (auto it: adjList) {
        int node = it.first;
        for (auto nbr: it.second) {
            indegree[nbr]++;
        }
    }

    // Step 2: Insert all independent nodes in queue for BFS
    queue<int> indNode;

    for (int i=0; i<numCourses; i++) {
        if (indegree[i] == 0) indNode.push(i);
    }
    
    // Step 3: Use BFS to get all courses that can be completed
    while (!indNode.empty()) {
        int node = indNode.front(); indNode.pop();
        topoSort.push_back(node);

        for (auto nbr: adjList[node]) {
            indegree[nbr]--;
            if (indegree[nbr] == 0) indNode.push(nbr);
        }
    }

    return topoSort;
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    // Create an adjacency list
    unordered_map<int, list<int>> adjList;
    for (auto it: prerequisites) {
        adjList[it[1]].push_back(it[0]);
    }
    
    // Get the topological sort of courses graph
    vector<int> ans = topologicalSort(adjList, numCourses);
    return ans.size() == numCourses ? ans : vector<int>{};
}


// 7.


// 8.


// 9.


// 10.



int main() {

    

    return 0;
}