#include <iostream>
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


// 18. 


// 19.


// 20.



int main() {

    

    return 0;
}