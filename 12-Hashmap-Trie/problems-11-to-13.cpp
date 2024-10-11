#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;


// 11. Top k frequent words
static bool cmp(pair<int, string>& a, pair<int, string>& b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    else {
        return a.first > b.first;
    }
}

vector<string> topKFrequent(vector<string>& words, int k) {
    // Step 1: Add all words in map
    unordered_map<string, int> mp;
    for (auto w: words) mp[w]++;

    // Step 2: Add all words in heap
    priority_queue<pair<int, string>> maxHeap;
    for (auto it: mp) {
        maxHeap.push({it.second, it.first});
    }

    // Step 3: Add top k words in answer array
    vector<pair<int, string>> freqAnswer;
    for (int i=0; i<words.size(); i++) {
        if (!maxHeap.empty()) {
            freqAnswer.push_back(maxHeap.top());
            maxHeap.pop();
        }
        else break;
    }

    // Step 4: Sort the answer array lexicographically
    sort(freqAnswer.begin(), freqAnswer.end(), cmp);

    // Step 5: Build final answer
    vector<string> ans;
    for (int i=0; i<k; i++) {
        ans.push_back(freqAnswer[i].second);
    }

    return ans;
}


// 12. 


// 13.



int main() {

    

    return 0;
}