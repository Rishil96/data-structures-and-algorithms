#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>
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


// 2. Number of Islands
void dfs(vector<vector<char>>& grid, int i, int j, vector<vector<bool>>& vis) {
    // Visit current cell
    vis[i][j] = 1;

    // Visit neighbours in 4 directions to make current island visited
    // Top
    if (i - 1 >= 0 && grid[i - 1][j] == '1' && !vis[i - 1][j]) dfs(grid, i - 1, j, vis);
    // Right
    if (j + 1 < grid[0].size() && grid[i][j + 1] == '1' && !vis[i][j + 1]) dfs(grid, i, j + 1, vis);
    // Bottom
    if (i + 1 < grid.size() && grid[i + 1][j] == '1' && !vis[i + 1][j]) dfs(grid, i + 1, j, vis);
    // Left
    if (j - 1 >= 0 && grid[i][j - 1] == '1' && !vis[i][j - 1]) dfs(grid, i, j - 1, vis);
}

int numIslands(vector<vector<char>>& grid) {
    vector<vector<bool>> vis(grid.size(), vector<bool>(grid[0].size(), false));
    int island = 0;

    // Loop through and visit each island one at a time
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[i].size(); j++) {
            if (grid[i][j] == '1' && !vis[i][j]) {
                island++;
                dfs(grid, i, j, vis);
            }
        }
    }

    return island;
}


// 3. Flood Fill
void fillHelper(vector<vector<int>>& img, int sr, int sc, int &color,vector<vector<bool>>& vis, int &ogColor) {
    // Fill current cell with color
    img[sr][sc] = color;
    vis[sr][sc] = 1;
    // Visit neighbours of the same color to fill it with color
    // Top
    if (sr - 1 >= 0 && img[sr - 1][sc] == ogColor && !vis[sr - 1][sc]) 
        fillHelper(img, sr - 1, sc, color, vis, ogColor);
    // Right
    if (sc + 1 < img[0].size() && img[sr][sc + 1] == ogColor && !vis[sr][sc + 1]) 
        fillHelper(img, sr, sc + 1, color, vis, ogColor);
    // Bottom
    if (sr + 1 < img.size() && img[sr + 1][sc] == ogColor && !vis[sr + 1][sc])
        fillHelper(img, sr + 1, sc, color, vis, ogColor);
    // Left
    if (sc - 1 >= 0 && img[sr][sc - 1] == ogColor && !vis[sr][sc - 1])
        fillHelper(img, sr, sc - 1, color, vis, ogColor);

}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    vector<vector<bool>> vis(image.size(), vector<bool>(image[0].size(), 0));
    int ogColor = image[sr][sc];
    fillHelper(image, sr, sc, color, vis, ogColor);
    return image;
}


// 4. Rotten Oranges
int orangesRotting(vector<vector<int>>& grid) {
    int time = 0;
    int freshOranges = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    // Use BFS to rot oranges
    queue<pair<int, pair<int, int>>> q;

    // Step 1: Insert all rotten oranges
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            // Keep track of fresh oranges to save time later
            if (grid[i][j] == 1) {
                freshOranges++;
            }
            // Push rotten orange in queue
            if (grid[i][j] == 2) {
                q.push({0, {i, j}});
            }
        }
    }

    // Step 2: Use BFS to rot all oranges
    while (!q.empty()) {
        // Get front orange
        auto frontItem = q.front(); q.pop();
        int currTime = frontItem.first;
        int currX = frontItem.second.first;
        int currY = frontItem.second.second;

        // Update time
        time = max(currTime, time);

        // Check if there are any fresh oranges in neighbouring cells and rot them
        // Top
        if (currX - 1 >= 0 && grid[currX-1][currY] == 1) {
            freshOranges--;
            grid[currX - 1][currY] = 2;
            q.push({currTime + 1, {currX - 1, currY}});
        }
        // Right
        if (currY + 1 < cols && grid[currX][currY+1] == 1) {
            freshOranges--;
            grid[currX][currY + 1] = 2;
            q.push({currTime + 1, {currX, currY + 1}});
        }
        // Bottom
        if (currX + 1 < rows && grid[currX+1][currY] == 1) {
            freshOranges--;
            grid[currX + 1][currY] = 2;
            q.push({currTime + 1, {currX + 1, currY}});
        }
        // Left
        if (currY - 1 >= 0 && grid[currX][currY-1] == 1) {
            freshOranges--;
            grid[currX][currY - 1] = 2;
            q.push({currTime + 1, {currX, currY - 1}});
        }
    }

    return freshOranges == 0 ? time : -1;
}


// 5. Course Schedule
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

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    // Create an adjacency list
    unordered_map<int, list<int>> adjList;
    for (auto it: prerequisites) {
        adjList[it[1]].push_back(it[0]);
    }
    
    // Get the topological sort of courses graph
    vector<int> ans = topologicalSort(adjList, numCourses);
    return ans.size() == numCourses;
}


int main() {
    

    return 0;
}