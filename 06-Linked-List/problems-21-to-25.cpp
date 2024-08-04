#include <iostream>
#include <unordered_map>
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
  Node(int x) {
    data = x;
    next = NULL;    
    }
};


// 21. Merge 2 sorted lists
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    // Merge both sorted list in below list pointers
    ListNode* ansHead = new ListNode(0);
    ListNode* ansTail = ansHead;

    while (list1 && list2) {
        // If current node of list1 is smaller than current node of list2
        if (list1 -> val <= list2 -> val) {
            ansTail -> next = list1;            // Attach list1 node to answer
            list1 = list1 -> next;              // Move list1 node to its next node
            ansTail = ansTail -> next;          // Update ansTail
            ansTail -> next = NULL;             // Remove link of ansTail with list1
        }
        else {
            ansTail -> next = list2;            // Attach list2 node to answer
            list2 = list2 -> next;              // Move list2 node to its next node
            ansTail = ansTail -> next;          // Update ansTail
            ansTail -> next = NULL;             // Remove link of ansTail with list2
        }
    }

    // Attach remaining nodes of both lists to answer
    if (list1) ansTail -> next = list1;
    else if (list2) ansTail -> next = list2;

    return ansHead -> next;
}


// 22. Kth node from the end
int getKthFromLast(Node *head, int k) {
    // Your code here
    Node* slow = head;
    Node* fast = head;
    
    // Move fast k nodes ahead of slow to make a window
    for (int i=0; i<k; i++) {
        if (fast) fast = fast -> next;
        else return -1;
    }
    
    // Now move both slow and fast till fast reaches NULL, and when that happens slow will be at Kth last node
    while (fast) {
        slow = slow -> next;
        fast = fast -> next;
    }
    
    return slow -> data;
}


// 23. Double a number represented as Linked List
ListNode* reverseList(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;

    while (curr) {
        ListNode* nextNode = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = nextNode;
    }

    return prev;
}

ListNode* doubleIt(ListNode* head) {
    ListNode* num = reverseList(head);
    
    ListNode* ans = NULL;
    int carry = 0;
    while (num) {
        int sum = num -> val + num -> val + carry;
        int digit = sum % 10;
        carry = sum / 10;
        ListNode* newNode = new ListNode(digit);

        if (!ans) {
            ans = newNode;
        }
        else {
            newNode -> next = ans;
            ans = newNode;
        }

        num = num -> next;
    }

    if (carry) {
        ListNode* newNode = new ListNode(carry);
        newNode -> next = ans;
        ans = newNode;
    }
    return ans;
}


// 24. Swapping nodes in a linked list
ListNode* swapNodes(ListNode* head, int k) {
    // Bring begin pointer to the kth node from beginning
    ListNode* begin = head;
    for (int i=0; i<k-1; i++) begin = begin -> next;

    // Using window logic, use temp as right of window and end pointer as left of window
    // Move the window till temp is a valid node and once its not, end pointer will be on kth last node
    ListNode* end = head;
    ListNode* temp = begin -> next;
    while (temp) {
        end = end -> next;
        temp = temp -> next;
    } 

    // Swap the values of begin and end nodes
    int tempVal = begin -> val;
    begin -> val = end -> val;
    end -> val = tempVal;

    return head;
}


// 25. Remove zero sum consecutive nodes from linked list
ListNode* removeZeroSumSublists(ListNode* head) {
    // Create answer list
    if(head == NULL) return head;
    unordered_map<int, ListNode*> prefixMap;
    ListNode* dummy = new ListNode(0);
    
    // Connect head to dummy node 
    dummy -> next = head;
    prefixMap[0] = dummy;

    // Variable to save prefix sum
    int preSum = 0;

    while(head != NULL){
        preSum += head -> val;
        // If prefix sum already exists in map, it means zero sum continuous nodes were found
        if (prefixMap.find(preSum) != prefixMap.end()) {
            
            ListNode* start = prefixMap[preSum];
            int prevSum = preSum;

            while(start != NULL && start != head) {
                start = start -> next;
                prevSum += start -> val;
                if(start != head) {
                    prefixMap.erase(prevSum);
                }
            }
            prefixMap[preSum] -> next = start -> next;
        }
        // Add the prefix sum with current node in map
        else {
            prefixMap[preSum] = head;
        }
        head = head -> next;
    }

    return dummy -> next;
}



int main() {

    

    return 0;
}