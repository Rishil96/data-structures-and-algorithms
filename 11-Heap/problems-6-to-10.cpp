#include <iostream>
#include <vector>
#include <queue>
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


// 8.


// 9.


// 10.



int main() {

    

    return 0;
}