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

void print(ListNode* head) {
    while (head) {
        cout << head -> val << " ";
        head = head -> next;
    }

    cout << endl;
    return ;
}


// 6. Remove Cycle from linked list
void removeCycle(ListNode* &head) {
    // Step 1: Find if cycle is present
    ListNode* slow = head;
    ListNode* fast = head;

    // Use slow fast approach to make slow and fast pointers meet
    while (fast) {
        fast = fast -> next;
        if (fast) {
            slow = slow -> next;
            fast = fast -> next;
        }
        if (slow == fast) break;
    }

    // Case where cycle is not present, fast will reach NULL 
    if (!fast) return ;

    // Step 2: Reset slow to head and start traversing with both slow and fast once
        slow = head;
        while (slow != fast) {      // Move slow and fast once till they meet again
            slow = slow -> next;
            fast = fast -> next;
        }
        
        // Step 3: Now slow and fast both are at the starting point of the loop
        // Set slow to head and move slow till we get to the point where slow points at the starting point of the loop
        while (slow -> next != fast) slow = slow -> next;
        slow -> next = NULL;
        
        return ;
}


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


// 9. Sort 0s, 1s and 2s in Linked List
ListNode* segregate(ListNode *head) {
    
    // Create head and tail nodes for each value 0, 1 and 2
    ListNode* zeroHead = new ListNode(0);
    ListNode* oneHead = new ListNode(1);
    ListNode* twoHead = new ListNode(2);
    
    ListNode* zeroTail = zeroHead;
    ListNode* oneTail = oneHead;
    ListNode* twoTail = twoHead;
    
    // Use current pointer to traverse the linked list
    ListNode* curr = head;
    
    // Separate out 0s, 1s and 2s into individual lists
    while (curr) {
        if (curr -> val == 0) {
            zeroTail -> next = curr;
            zeroTail = curr;
            curr = curr -> next;
            zeroTail -> next = NULL;
        }
        else if (curr -> val == 1) {
            oneTail -> next = curr;
            oneTail = curr;
            curr = curr -> next;
            oneTail -> next = NULL;
        }
        else {
            twoTail -> next = curr;
            twoTail = curr;
            curr = curr -> next;
            twoTail -> next = NULL;
        }
    }
    
    // Remove initial placeholder node that was used to smoothly add new nodes in tail
    if (zeroHead == zeroTail) {
        zeroHead = NULL;
        zeroTail = NULL;
    }
    else zeroHead = zeroHead -> next;

    if (oneHead == oneTail) {
        oneHead = NULL;
        oneTail = NULL;
    }
    else oneHead = oneHead -> next;
    
    if (twoHead == twoTail) {
        twoHead = NULL;
        twoTail = NULL;
    }
    else twoHead = twoHead -> next;
    
    // If One list exists then merge two head at the tail of one list or else add two list directly on onehead
    if (oneHead) oneTail -> next = twoHead;
    else oneHead = twoHead; 
    
    // If zero list exists then merge one head with zero tail or else add one head directly on zero head 
    if (zeroHead) {
        zeroTail -> next = oneHead;
    }
    else zeroHead = oneHead;
    
    return zeroHead;
}


// 10. Add numbers in a list
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // Temporary variables to traverse through list
    ListNode* temp1 = l1;
    ListNode* temp2 = l2;

    // Add both Linked List
    ListNode* ansHead = NULL;
    ListNode* ansTail = NULL;

    int carry = 0;

    // Traverse both lists together till digits are present
    while (temp1 && temp2) {
        int sum = temp1 -> val + temp2 -> val + carry;
        int digit = sum % 10;
        carry = sum / 10;
        ListNode* newNode = new ListNode(digit);
        if (!ansHead) {
            ansHead = newNode;
            ansTail = newNode;
        }
        else {
            ansTail -> next = newNode;
            ansTail = newNode;
        }
        temp1 = temp1 -> next;
        temp2 = temp2 -> next;
    }

    // Traverse left list if digits are present
    while (temp1) {
        int sum = carry + temp1 -> val;
        int digit = sum % 10;
        carry = sum / 10;
        
        ListNode* newNode = new ListNode(digit);
        if (!ansHead) {
            ansHead = newNode;
            ansTail = newNode;
        }
        else {
            ansTail -> next = newNode;
            ansTail = newNode;
        }
        temp1 = temp1 -> next;
    }
    
    // Traverse right list if digits are present
    while (temp2) {
        int sum = carry + temp2 -> val;
        int digit = sum % 10;
        carry = sum / 10;
        
        ListNode* newNode = new ListNode(digit);
        if (!ansHead) {
            ansHead = newNode;
            ansTail = newNode;
        }
        else {
            ansTail -> next = newNode;
            ansTail = newNode;
        }
        temp2 = temp2 -> next;
    }

    while (carry != 0) {
        int sum = carry;
        int digit = carry % 10;
        carry = carry / 10;

        ListNode* newNode = new ListNode(digit);
        ansTail -> next = newNode;
        ansTail = newNode;
    }

    return ansHead;
}



int main() {

    ListNode* head = new ListNode(1);
    ListNode* tail = new ListNode(5);
    head -> next = new ListNode(2);
    head -> next -> next = new ListNode(3);
    head -> next -> next -> next = new ListNode(4);
    head -> next -> next -> next -> next = tail;
    tail -> next = head -> next;

    // print(head);         // This will run infinitely as loop exits in linked list
    removeCycle(head);
    print(head);

    return 0;
}