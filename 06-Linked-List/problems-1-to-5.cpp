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


// 1. Reverse Linked List
ListNode* reverseList(ListNode* head) {
    // Use 3 nodes to perform reversal
    ListNode* prevNode = NULL;
    ListNode* currNode = head;

    while (currNode) {
        ListNode* nextNode = currNode -> next;  // Get next node in list
        currNode -> next = prevNode;            // Point current node to its prev node
        prevNode = currNode;                    // Move prev node to current node
        currNode = nextNode;                    // Move current node to next node
    }

    return prevNode;
}


// 2. Middle of Linked List
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;      // Use this pointer to move one node ahead
    ListNode* fast = head;      // Use this pointer to move two steps ahead

    // Run loop till fast pointer goes out of list
    while (fast) {
        fast = fast -> next;
        if (fast) {
            slow = slow -> next;
            fast = fast -> next;
        }
    }

    return slow;
}


// 3. Reverse nodes in k-group
int getLength(ListNode* head) {
    int len = 0;

    while (head) {
        len++;
        head = head -> next;
    }
    
    return len;
}

pair<ListNode*, ListNode*> reverseList(ListNode* head, int k) {
    // Use 3 pointers to reverse list
    ListNode* prevNode = NULL;
    ListNode* currNode = head;
    ListNode* nextNode = NULL;

    // Reverse list for k elements

    while (k-- && currNode) {
        nextNode = currNode -> next;
        currNode -> next = prevNode;
        prevNode = currNode;
        currNode = nextNode; 
    }

    // prevNode will be the new head and nextNode will be the node just beyond the current k group so the head of remaining list
    return {prevNode, nextNode};
}

ListNode* reverseKGroup(ListNode* head, int k) {
    int length = getLength(head);
    // Base Case: If current head length is less than k return head
    if (length < k) {
        return head;
    }

    // Ek Case: Reverse current k group
    // Reverse function will return 2 ListNodes, 1. head after reversal and next head to reverse
    pair<ListNode*, ListNode*> reversedItems = reverseList(head, k);
    // Old head will be the new tail of k reversed list. Use it to attach next k reversed items of list
    head -> next = reverseKGroup(reversedItems.second, k);

    return reversedItems.first;
}


// 4. Linked List Cycle
bool hasCycle(ListNode *head) {
    // Use 2 pointers slow and fast to traverse the list at different speed
    ListNode* slow = head;
    ListNode* fast = head;

    // Move fast twice and slow once every iteration
    while (fast) {
        fast = fast -> next;
        if (fast) {
            slow = slow -> next;
            fast = fast -> next;
        }

        // If slow and fast pointers meet at a node, it means loop is present
        if (slow == fast) return true;
    }

    // If fast pointer reaches NULL, it means no loop present
    return false;
}


// 5. Linked List Cycle 2
ListNode *detectCycle(ListNode *head) {
    if (!head) return head; 

    // Use slow and fast pointer to detect cycle
    ListNode* slow = head;
    ListNode* fast = head;

    // Move fast twice and slow once till they both meet or fast reaches NULL
    do  {
        fast = fast -> next;
        if (fast) {
            slow = slow -> next;
            fast = fast -> next;
        }
        if (slow == fast) break;
    } while (fast);

    // Return fast i.e. NULL if cycle is not present
    if (!fast) return fast;

    // Reset slow to head and start moving both pointers once every iteration till they meet again
    slow = head;
    while (slow != fast) {
        slow = slow -> next;
        fast = fast -> next;
    }

    // Once they meet again they are on the starting point of the array
    return slow;
}




int main() {

    

    return 0;
}