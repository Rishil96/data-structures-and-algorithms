#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// 11. Word Ladder 2
vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) {
    
    // Build a map to access dictionary words in constant time
    unordered_map<string, bool> wordMap;
    for (auto w: wordList) wordMap[w] = 1;

    // Variable to store answer and queue to perform BFS
    vector<vector<string>> ans;
    queue<pair<vector<string>, int>> q;

    // Check if endword is an available word, if not then endword cannot be reached, return blank array as ans
    if (wordMap.find(endWord) == wordMap.end()) return ans;

    // Push beginWord as a vector to start a sequence in BFS
    q.push({{beginWord}, 1});
    wordMap[beginWord] = 0;

    // Array to keep track of used words
    vector<string> remove;
    int prevLevel = -1;

    // Use queue to build sequences via BFS
    while (!q.empty()) {
        auto frontNode = q.front(); q.pop();
        auto currPath = frontNode.first;
        string word = currPath.back();
        int level = frontNode.second;

        // Update level
        if (prevLevel != level) {
            for (auto w: remove) wordMap[w] = 0;
            prevLevel = level;
        }

        // Answer push case, when endword is reached, push sequence in ans array
        if (word == endWord) {
            ans.push_back(currPath);
            continue;
        }

        // Try to move to next word from current word in sequence array
        for (int i=0; i<word.size(); i++) {
            char currCh = word[i];
            for (char ch='a'; ch<='z'; ch++) {
                word[i] = ch;
                if (wordMap[word] == 1) {
                    auto temp = currPath;
                    temp.push_back(word);
                    q.push({temp, level+1});
                    remove.push_back(word);
                }
            }
            word[i] = currCh;
        }
    }

    return ans;
}


// 12. Minimum multiplications to reach end
int minimumMultiplications(vector<int>& arr, int start, int end) {
    /*
    We use an array to build the answer where each index i is the element and its value
    will be the number of operations required to reach i.
    */
    // Step 1: Initialize variables
    int MOD = 100000;                   // MOD value
    queue<int> q;                       // queue to perform BFS
    vector<int> ans(100000, -1);        // Ans array to store minimum jumps to reach i
    q.push(start);                      // 
    ans[start] = 0;
    
    // Step 2: Use BFS and try to reach end node
    while (!q.empty()) {
        int frontNode = q.front(); q.pop();
        if (frontNode == end) return ans[frontNode];
        
        // Loop through each arr element and perform operation on frontNode
        for (auto num: arr) {
            int newNode = (frontNode * num) % MOD;
            // If no answer existed for newNode, write answer
            // Answer is 1 operation more from what is required to reach frontNode
            // as we performed the operation on frontNode to reach newNode
            if (ans[newNode] == -1) {
                ans[newNode] = 1 + ans[frontNode];
                q.push(newNode);
            }
        }
    }
    
    return -1;
}
 

// 13.


// 14.


// 15.



int main() {

    

    return 0;
}