#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// 6. Merge k sorted lists
class compare {
    public:
    bool operator()(ListNode* a, ListNode* b) {
        return a -> val > b -> val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    // Min heap to hold listnodes
    priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;

    // Build sorted list using 2 pointers
    ListNode* head = NULL;
    ListNode* tail = head;

    // Add all list heads in heap
    for (int i=0; i<lists.size(); i++) {
        if (lists[i] == NULL) continue;
        minHeap.push(lists[i]); 
    }

    // Run loop till heap has elements
    while (!minHeap.empty()) {
        ListNode* topNode = minHeap.top(); minHeap.pop();
        // Add smallest node to the sorted list
        if (!head) {
            head = tail = topNode;
        }
        else {
            tail -> next = topNode;
            tail = tail -> next;
        }

        // If current smallest node has more elements, add the next element in heap
        if (topNode -> next) minHeap.push(topNode -> next);
        topNode -> next = NULL;
    }

    return head;
}


// 7.


// 8. Remove stones to minimize the total
int minStoneSum(vector<int>& piles, int k) {
    // Add all piles of stone in maxHeap
    priority_queue<int> maxHeap;
    for (auto p: piles) maxHeap.push(p);

    // For k iterations, remove piles/2 where pile is the current largest pile in heap and add it back in heap
    while (k--) {
        int currPile = maxHeap.top(); maxHeap.pop();
        currPile -= (currPile / 2);
        maxHeap.push(currPile);
    }

    // Add all the piles in a variable and return it
    int ans = 0;
    while (!maxHeap.empty()) {
        ans += maxHeap.top(); maxHeap.pop();
    }

    return ans;
}


// 9. Reorganize String
string reorganizeString(string s) {
    // Get frequency of each character
    unordered_map<char, int> freq;
    for (auto ch: s) freq[ch]++;

    // Add them to max heap
    priority_queue<pair<int, char>> maxHeap;
    for (auto item: freq) {
        maxHeap.push({item.second, item.first});
    }

    string ans;

    // Edge case: If a character has frequency more than half of the total s size then reorganize not possible
    if (!maxHeap.empty() && maxHeap.top().first > (s.size() / 2 + s.size() % 2)) return ans;

    // Always pop 2 elements together and use them in answer string
    while (maxHeap.size() > 1) {
        // Pop top 2 freq characters 
        auto top1 = maxHeap.top(); maxHeap.pop();
        auto top2 = maxHeap.top(); maxHeap.pop();

        // Add both characters in answer
        ans += top1.second;
        ans += top2.second;

        // Decrement frequency after using it in main answer
        top1.first--;
        top2.first--;

        // If frequency greater than 1 insert them back in heap
        if (top1.first > 0) maxHeap.push(top1);
        if (top2.first > 0) maxHeap.push(top2); 
    }

    // Add last remaining element in final answer
    if (!maxHeap.empty()) ans += maxHeap.top().second;

    return ans;
}


// 10. Longest Happy String
string longestDiverseString(int a, int b, int c) {
    // Push a, b and c in maxHeap
    priority_queue<pair<int, char>> maxHeap;
    if (a > 0) maxHeap.push({a, 'a'});
    if (b > 0) maxHeap.push({b, 'b'});
    if (c > 0) maxHeap.push({c, 'c'});

    // Start building happy string
    string ans;

    while (maxHeap.size() > 1) {
        // Pop top 2 elements from heap 
        auto top1 = maxHeap.top(); maxHeap.pop();
        auto top2 = maxHeap.top(); maxHeap.pop();

        // Add top element
        ans += top1.second;
        top1.first--;

        // If top1 element still has more frequency than top2 then add both elements once 
        if (top1.first > top2.first) {
            ans += top1.second;
            ans += top2.second;
            top1.first--;
            top2.first--;
        }

        // Add back elements in heap whose frequencies are still over 0
        if (top1.first > 0) maxHeap.push(top1);
        if (top2.first > 0) maxHeap.push(top2);
    }
    
    // Check if heap is not empty and the last heap element is not at the end of the ans string, if yes then add it to our answer
    if ((ans.empty()) || (!maxHeap.empty() && maxHeap.top().second != ans.back())) {
        ans += maxHeap.top().second;
        if (maxHeap.top().first - 1 > 0) ans += maxHeap.top().second;
    }

    return ans;
}



int main() {

    

    return 0;
}