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
	struct Node * next;
	struct Node * bottom;
	
	Node(int x){
	    data = x;
	    next = NULL;
	    bottom = NULL;
	}	
};


// 11. Remove nth node from end of list
int getLen(ListNode* head) {
    int len = 0;

    while (head) {
        len++;
        head = head -> next;
    }

    return len;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    // 1. Get length of list
    int len = getLen(head);
    int delNodeIndex = len - n;

    // 2. Edge Case for first element removal
    if (delNodeIndex == 0) return head -> next;

    // 3. Use 2 pointers to reach to the element before the deletion node
    ListNode* slow = NULL;
    ListNode* fast = head;

    while (delNodeIndex--) {
        slow = fast;
        fast = fast -> next;
    }

    // 4. Remove the node in the middle of slow and fast
    slow -> next = fast -> next;

    return head;
}

ListNode* removeNthFromEnd2(ListNode* head, int n) {
    // 1. Edge Case with single element in list
    if (head -> next == NULL) return NULL;

    // 2. Calculate the length of the list
    int length = 0;
    ListNode* temp = head;
    while (temp) {
        temp = temp -> next;
        length++;
    }

    // 3. Update length to point to the nth last index from end
    length -= n;

    // 4. Edge Case: Removal of first node from the list
    if (length == 0) return head -> next;

    // 5. Use temp pointer to move it to the node just before the node we want to delete
    temp = head;
    while (--length && temp) {
        temp = temp -> next;
    }

    // 6. Remove the node ahead of temp and return head
    if (temp -> next) {
        temp -> next = temp -> next -> next;
    }
    else {
        temp -> next = NULL;
    }
    return head;
}


// 12. Intersection of 2 linked lists
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    // 1. Use 2 pointers to initially traverse both lists
    ListNode* tempA = headA;
    ListNode* tempB = headB;

    // 2. Traverse both lists till any one of the pointer reaches NULL
    while (tempA && tempB) {
        // Special Case where intersection can be found directly
        if (tempA == tempB) return tempA;
        tempA = tempA -> next;
        tempB = tempB -> next;
    }

    // 3. Calculate by how much the longer list is longer than the shorter list
    bool isALarger = (tempA) ? true : false;
    int length = 0;

    // If A is larger list, then traverse till the end to get remaining length
    while (tempA) {
        length++;
        tempA = tempA -> next;
    } 

    // If B is larger list, then traverse till the end to get remaining length
    while (tempB) {
        length++;
        tempB = tempB -> next;
    }

    // 4. Reset tempA and tempB and initially move the longer list length times 
    tempA = headA;
    tempB = headB;

    if (isALarger) {
        while (length--) {
            tempA = tempA -> next;
        }
    }
    else {
        while (length--) {
            tempB = tempB -> next;
        } 
    }

    // 5. Move tempA and tempB till they are equal
    while (tempA && tempB && tempA != tempB) {
        tempA = tempA -> next;
        tempB = tempB -> next;
    }

    return tempA;
}


// 13. Sort Linked List
int getLength(ListNode* head) {
    int len = 0;

    while (head) {
        len++;
        head = head -> next;
    }

    return len;
}

ListNode* mergeLL(ListNode* leftHead, ListNode* rightHead) {
    // Merge 2 sorted Linked List
    ListNode* head = NULL;
    ListNode* tail = NULL;

    // Add smaller nodes one by one from left and right lists by comparison
    while (leftHead && rightHead) {
        if (leftHead -> val <= rightHead -> val) {
            if (!head) {
                head = leftHead;
                tail = head;
                leftHead = leftHead -> next;
            }
            else {
                tail -> next = leftHead;
                tail = tail -> next;
                leftHead = leftHead -> next;
            }
        }
        else {
            if (!head) {
                head = rightHead;
                tail = head;
                rightHead = rightHead -> next;
            }
            else {
                tail -> next = rightHead;
                tail = tail -> next;
                rightHead = rightHead -> next;
            }
        }
    }

    // Add whatever remains of left/right list to the tail of answer list
    if (leftHead) tail -> next = leftHead;
    if (rightHead) tail -> next = rightHead;

    return head;
}

ListNode* mergeSortLL(ListNode* head, int start, int end) {
    // Base Case
    if (start >= end) return head;

    // Ek Case: Break linked list into 2 from mid
    int mid = start + (end - start) / 2;
    ListNode* temp = head;

    // Reach mid node using temp ptr and break the link and save right head
    for (int i=0; i<mid; i++) {
        if (temp) temp = temp -> next;
    }

    ListNode* head2 = temp -> next;
    temp -> next = NULL;

    // Sort Left list
    head = mergeSortLL(head, 0, mid);

    // Sort right list
    head2 = mergeSortLL(head2, 0, end - mid - 1);

    // Merge left and right list that was sorted
    return mergeLL(head, head2);
}

ListNode* sortList(ListNode* head) {
    // 1. Get Length of linked list
    int start = 0;
    int end = getLength(head) - 1;

    return mergeSortLL(head, start, end);
}


// 14. Flatten Linked List
Node* flattenHelper(Node* currHead) {
    // Base Case: No next pointer means no next list
    if (!currHead) {
        return currHead;
    }
    
    // Recursive Call to reach the last list first so merging can be done from end to start
    Node* nextHead = flattenHelper(currHead -> next);
    
    // Merge current and next head and return the head of merged list
    Node* head = NULL;
    Node* tail = NULL;
    
    // Apply the algorithm of merging 2 sorted linked list to merge them
    while (currHead && nextHead) {
        if (currHead -> data < nextHead -> data) {
            if (!head) {
                head = tail = currHead;
            }
            else {
                tail -> bottom = currHead;
                tail = tail -> bottom;
            }
            currHead = currHead -> bottom;
        }
        else {
            if (!head) {
                head = tail = nextHead;
            }
            else {
                tail -> bottom = nextHead;
                tail = tail -> bottom;
            }
            nextHead = nextHead -> bottom;
        }
    }
    
    // If currhead has remaining nodes, add them to the end
    if (currHead && head) {
        tail -> bottom = currHead;
    }
    else if (currHead && !head) {
        head = tail = currHead;
    }
    
    // If nextHead has remaining nodes, add them to the end
    if (nextHead && head) {
        tail -> bottom = nextHead;
    }
    else if (nextHead && !head) {
        head = tail = nextHead;
    }
    
    return head;
}

Node *flatten(Node *root) {
    return flattenHelper(root);
}


// 15. Copy Linked List with Random Pointer



int main() {

    

    return 0;
}