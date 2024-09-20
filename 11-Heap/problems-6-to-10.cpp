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


// 7. Smallest Range in K list
// Class to keep track of all the elements and their position in minHeap
class Info
{
public:
    int data;
    int row;
    int col;

    Info(int data, int row, int col) {
        this -> data = data;
        this -> row = row;
        this -> col = col;
    }
};


// MinHeap comparator for Info class    
class compare2
{
public:
    bool operator()(Info* a, Info* b) {
        return a -> data > b -> data;
    }
};

vector<int> smallestRange(vector<vector<int>>& nums) {
    // Step 1: Create min priority queue and variable to keep track of max and min elements
    int maxElement = INT_MIN;
    int minElement = INT_MAX;
    priority_queue<Info*, vector<Info*>, compare2> minHeap;

    // Step 2: Add first elements from each array
    for (int i=0; i<nums.size(); i++) {
        int element = nums[i][0];
        int row = i;
        int col = 0;
        // Create info object about current element
        Info* newElement = new Info(element, row, col);
        minHeap.push(newElement);
        // Update max and min elements
        maxElement = max(maxElement, element);
        minElement = min(minElement, element);
    }

    int ansStart = minElement;
    int ansEnd = maxElement;
    
    // Step 3: Process remaining elements
    while (!minHeap.empty()) {
        Info* topElement = minHeap.top(); minHeap.pop();
        // Update minElement and check if range has reduced
        minElement = topElement -> data;
        if (maxElement - minElement < ansEnd - ansStart) {
            ansStart = minElement;
            ansEnd = maxElement;
        }

        // Insert new element from current row array if it exists
        if (topElement -> col + 1 < nums[topElement -> row].size()) {
            int element = nums[topElement -> row][topElement -> col + 1];
            // Update max element
            maxElement = max(element, maxElement);
            Info* newElement = new Info(element, topElement -> row, topElement -> col + 1);
            minHeap.push(newElement);
        }
        // If the given array has no more new elements then break as it will go out of range
        else {
            break;
        }
    } 

    return vector<int> {ansStart, ansEnd};
}   


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