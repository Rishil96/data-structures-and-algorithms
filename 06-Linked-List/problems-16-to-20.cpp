#include <iostream>
#include <vector>
using namespace std;


// ListNode datastructure
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct Node
{
    int data;
    struct Node *next;

    Node(int x){
        data = x;
        next = NULL;
    }

};


// 16. Rotate List
int length(ListNode* head) {
    int len = 0;
    while (head) {
        ++len;
        head = head -> next;
    }
    return len;
}

ListNode* rotateRight(ListNode* head, int k) {
    // Calculate length of list and bring k down to a value that is <= length
    int len = length(head);                 
    k = (len) ? k % len : k;

    // Edge Cases: list with 0 or 1 nodes or k = 0
    if (len == 0 || len == 1 || k == 0) return head;

    // Use 2 pointers with a window of k
    ListNode* slow = head;
    ListNode* fast = head;

    // Move fast k nodes ahead to create this window
    for (int i=0; i<k; i++) fast = fast -> next;

    // Move the window till fast pointer reaches last node in the list
    while (fast -> next) {
        slow = slow -> next;
        fast = fast -> next;
    }

    // Now slow will be at the node just before our new head node
    ListNode* newHead = slow -> next;           // Create new head pointer
    slow -> next = NULL;                        // Disconnect new tail from new head
    fast -> next = head;                        // Attach old head to new tail

    return newHead;
}


// 17. Delete n nodes after m nodes
void linkdelete(struct Node **head, int n, int m) {
    // Use slow and fast pointer
    // slow -> points at node that we want to keep
    // fast -> traverses list to the next node we want to keep
    
    Node* slow = *head;
    Node* fast = *head;
    
    while (slow && fast) {
        // Skip M nodes
        for (int i=0; i<m-1; i++) {
            if (slow) slow = slow -> next;
        }
        
        // Move fast to slow -> next and go n nodes ahead to delete them
        if (slow) fast = slow -> next;
        
        for (int i=0; i<n; i++) {
            if (fast) fast = fast -> next;
        }
        
        // Delete n nodes by pointing slow directly to fast and update slow
        if (slow) {
            slow -> next = fast;
            slow = fast;
        }
    }
    
    return ;
}


// 18. Minimum/Maximum number of nodes between critical points
vector<int> nodesBetweenCriticalPoints(ListNode* head) {
    // Store ans in variable
    vector<int> ans{-1, -1};

    // Edge Case
    if (!head || !head -> next) return ans;

    // Use 2 pointers to find critical points
    ListNode* prevNode = head;
    ListNode* currNode = head -> next;

    int index = 1;

    int firstCriticalIndex = -1;
    int recentCriticalIndex = -1;

    while (currNode) {
        cout << currNode -> val << endl;
        // Check first if curr node has both prev and next node
        if (prevNode && currNode -> next) {
            
            // Check if current node is a critical point i.e. local minima/maxima
            bool isLocalMinima = prevNode -> val > currNode -> val && 
                                    currNode -> val < currNode -> next -> val;
            bool isLocalMaxima = prevNode -> val < currNode -> val && 
                                    currNode -> val > currNode -> next -> val;
            
            // Update both indexes in case of current node being a critical point
            if (isLocalMinima || isLocalMaxima) {
                if (firstCriticalIndex == -1) {
                    firstCriticalIndex = index;
                    recentCriticalIndex = index;
                } 
                else {
                    // Calculate minimum distance between current and previous critical point
                    ans[0] = (ans[0] == -1) ? index - recentCriticalIndex : min(ans[0], index - recentCriticalIndex);
                    recentCriticalIndex = index;
                }
            }
        }

        prevNode = currNode;
        currNode = currNode -> next;
        index++;
    }

    // Calculate maximum distance between first and last critical point
    ans[1] = (firstCriticalIndex != recentCriticalIndex) ? max(ans[1], recentCriticalIndex - firstCriticalIndex) : -1;

    return ans;
}

vector<int> nodesBetweenCriticalPointsBetter(ListNode* head) {
    vector<int> ans(2, -1);
    // Traversal pointers
    ListNode* prevNode = NULL;
    ListNode* currNode = head;

    // Critical Points tracker
    int index = 0;
    int firstCritical = -1;
    int latestCritical = -1;

    while (currNode -> next) {
        // Check if local minima
        bool isMinima = prevNode && currNode -> val < prevNode -> val && currNode -> val < currNode -> next -> val;
        // Check if local maxima
        bool isMaxima = prevNode && currNode -> val > prevNode -> val && currNode -> val > currNode -> next -> val;

        if (isMinima || isMaxima) {
            if (firstCritical == -1) {
                firstCritical = index;
                latestCritical = index;
            }
            else {
                // Update minimum distance
                ans[0] = ans[0] == -1 ? index - latestCritical : min(ans[0], index - latestCritical);
                // Update Maximum distance
                ans[1] = ans[1] == -1 ? index - firstCritical : max(ans[1], index - firstCritical);
                latestCritical = index;
            }
        }

        prevNode = currNode;
        currNode = currNode -> next;
        index++;
    }

    return ans;
}


// 19. 


// 20.



int main() {

    

    return 0;
}