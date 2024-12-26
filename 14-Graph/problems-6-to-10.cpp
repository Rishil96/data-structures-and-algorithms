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


// 8.


// 9.


// 10.



int main() {

    

    return 0;
}