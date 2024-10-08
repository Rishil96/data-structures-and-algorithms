#include <iostream>
#include <unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


// 6. Intersection of 2 lists
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    unordered_map<ListNode*, bool> mp;
    
    // Add all nodes of headA in map
    while (headA) {
        mp[headA] = 1;
        headA = headA -> next;
    }

    // Check if headB element exists in headA and return the first such element
    while (headB) {
        if (mp[headB]) return headB;
        headB = headB -> next;
    }

    return NULL;
}


// 7.


// 8.


// 9.


// 10.



int main() {

    

    return 0;
}