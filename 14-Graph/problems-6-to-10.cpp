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


// 9.


// 10.



int main() {

    

    return 0;
}