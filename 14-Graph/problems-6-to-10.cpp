#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>
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


// 7. Word Ladder
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    // Step 1: Create a map of available words
    unordered_map<string, bool> wordMap;
    for (auto w: wordList) wordMap[w] = 1;

    // Step 2: Check if end word is available in map
    if (!wordMap[endWord]) return 0;

    // Step 3: Use BFS to reach the end word from start word
    queue<pair<string, int>> q;
    q.push({beginWord, 1});
    wordMap[beginWord] = 0;

    while (!q.empty()) {
        auto frontNode = q.front(); q.pop();
        string currWord = frontNode.first;
        int currTime = frontNode.second;

        // Check if currword is endword
        if (currWord == endWord) return currTime;

        // Find a word that only has 1 different letter than currWord
        for (int i=0; i<currWord.size(); i++) {
            char currLetter = currWord[i];
            // Loop through all letters
            for (char letter='a'; letter<='z'; letter++) {
                if (letter == currLetter) continue;
                // Place new letter at current position and check if it exists in map
                currWord[i] = letter;
                // If new word exists in map, add it in queue
                if (wordMap[currWord]) {
                    q.push({currWord, currTime + 1});
                    // Always scrap the word from map after it is used once to not fall into infinite loop
                    wordMap[currWord] = 0;
                }
            }
            // Backtrack to original current word
            currWord[i] = currLetter;
        }
    }

    return 0;
}


// 8. Path with minimum effort
int minimumEffortPath(vector<vector<int>>& heights) {
    // Step 1: Create variables for traversal
    int rows = heights.size();
    int cols = heights[0].size();
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    // Step 2: Insert starting point in heap/priority queue
    pq.push({0, {0, 0}});
    dist[0][0] = 0;

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    // Step 3: Start Dijkstra's algorithm to calculate shortest distance
    while (!pq.empty()) {
        // Get node with shortest distance
        auto topNode = pq.top(); pq.pop();
        int topDist = topNode.first;
        int X = topNode.second.first;
        int Y = topNode.second.second;

        // If we are on destination variable then return answer
        if (X == rows - 1 && Y == cols - 1) return dist[X][Y];

        // Go through all of its neighbours and insert them in queue
        for (int i=0; i<4; i++) {
            int newX = X + dx[i];
            int newY = Y + dy[i];

            // Calculate the absolute height difference between nodes
            if (newX >= 0 && newY >= 0 && newX < rows && newY < cols) {
                int currDiff = abs(heights[X][Y] - heights[newX][newY]);
                int newMax = max(currDiff, topDist);
            
                // If current difference is smaller than what we have in distance array, then update it
                if (newMax < dist[newX][newY]) {
                    dist[newX][newY] = newMax;
                    pq.push({newMax, {newX, newY}});
                }
            }
        }
    }

    return dist[rows - 1][cols - 1];
}


// 9. Critical Connections in a network
void findBridges(int src, int parent, int &timer, vector<int>& tin, vector<int>& low, unordered_map<int, bool>& visited, vector<vector<int>>& ans, unordered_map<int, list<int>> &adjList) {
    // Step 1: Update timer for source node
    visited[src] = 1;
    tin[src] = timer;
    low[src] = timer;
    timer++;

    // Step 2: Visit neighbours of source
    for (auto nbr: adjList[src]) {
        // Ignore parent to go back to the node we came from
        if (nbr == parent) continue;

        // Visit neighbour if not visited
        if (!visited[nbr]) {
            findBridges(nbr, src, timer, tin, low, visited, ans, adjList);
            // Update low of src if it can be visited faster via nbr
            low[src] = min(low[src], low[nbr]);

            // Bridge Condition
            if (low[nbr] > tin[src]) {
                ans.push_back({src, nbr});
            }
        }
        // Else just update if src can be visited faster via nbr
        else  {
            low[src] = min(low[src], low[nbr]);
        }
    }
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    // Step 1: Create adjacency list
    unordered_map<int, list<int>> adjList;

    for (int i=0; i<connections.size(); i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Step 2: Create variables for algorithm
    vector<vector<int>> ans;
    int timer = 0;
    vector<int> tin(n);
    vector<int> low(n);
    unordered_map<int, bool> vis;

    // Step 3: Find bridges which are critical connection to keep the network together
    findBridges(0, -1, timer, tin, low, vis, ans, adjList);
    return ans;
}


// 10. Eventual Safe States
bool cycleDetectionDFS(int src, vector<int> adj[], unordered_map<int, bool> &vis, unordered_map<int, bool>& dfsVis, int safeNodes[]) {
    vis[src] = true;
    dfsVis[src] = true;
    safeNodes[src] = 0;
    for (auto nbr : adj[src]) {
        if (!vis[nbr]) {
            bool recAns = cycleDetectionDFS(nbr, adj, vis, dfsVis, safeNodes);
            if (recAns) return recAns;
        }
        else {
            if (dfsVis[nbr]) return true;
        }
    }
    
    dfsVis[src] = false;
    safeNodes[src] = 1;
    return false;
}

vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
    // Observation: If a node leads to a cycle, then its definitely not a safe node
    // Find nodes that are part of cycle to mark them as unsafe
    // Step 1: Declare variables
    vector<int> ans;
    unordered_map<int, bool> vis;
    unordered_map<int, bool> dfsVis;
    int safeNodes[V] = {0};
    
    // Step 2: Visit all nodes
    for (int node=0; node<V; node++) {
        if (!vis[node]) cycleDetectionDFS(node, adj, vis, dfsVis, safeNodes);
    }
    
    // Step 3: Store safe nodes in ans array
    for (int src=0; src<V; src++) {
        if (safeNodes[src]) ans.push_back(src);
    }
    
    return ans;
}



int main() {

    

    return 0;
}