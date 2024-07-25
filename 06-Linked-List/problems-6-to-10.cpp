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


// 6.


// 7. Check if linked list is a palindrome
bool isPalindrome(ListNode* head) {
    // Step 0: Base Case
    if (!head || !head -> next) return 1;

    // Step 1: Find the middle of the list
    ListNode* head2 = head;
    ListNode* temp = head -> next;

    while (temp) {
        temp = temp -> next;
        if (temp) {
            head2 = head2 -> next;
            temp = temp -> next;
        }
    }

    // Step 2: Split the linked list from middle
    temp = head2 -> next;
    head2 -> next = NULL;
    head2 = temp;

    // Step 3: Reverse the second list and get its new head 
    ListNode* prevNode = NULL;
    ListNode* currNode = head2;

    while (currNode) {
        ListNode* nextNode = currNode -> next;
        currNode -> next = prevNode;
        prevNode = currNode;
        currNode = nextNode;
    }

    head2 = prevNode;

    // Step 4: Compare the two list for palindrome
    while (head && head2) {
        if (head -> val != head2 -> val) return 0;
        head = head -> next;
        head2 = head2 -> next;
    }

    return 1;
}


// 8. Remove duplicates from sorted list
ListNode* deleteDuplicates(ListNode* head) {
    // Edge Case: empty list
    if (!head) return head;

    // Use 2 pointers slow and fast where fast will be compared to slow for duplicates
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast) {
        // If slow and fast have equal values then move fast ahead by 1 node
        if (fast -> val == slow -> val) fast = fast -> next;
        // When slow and fast have different values
        else {
            // Point slow -> next to fast to skip duplicates
            slow -> next = fast;
            // Set slow pointer equal to fast to start duplicate comparison for next element
            slow = fast;
            // Move fast ahead by 1
            fast = fast -> next;
        }
    }

    // Set slow -> next to fast to skip the duplicates at the end
    slow -> next = fast;

    return head;
}


// 9. 


// 10.



int main() {

    

    return 0;
}