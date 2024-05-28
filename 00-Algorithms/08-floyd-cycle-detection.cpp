#include <iostream>
using namespace std;

class ListNode
{
    public:
        int val;
        ListNode* next;
        ListNode(int val) {
            this -> val = val;
            this -> next = NULL;
        }
};


bool detectCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast) {
        fast = fast -> next;
        if (fast) {
            slow = slow -> next;
            fast = fast -> next;
        }
        if (slow == fast) return 1;
    }

    return 0;
}


int main() {

    ListNode* root = new ListNode(1);
    root -> next = new ListNode(2);
    root -> next -> next = new ListNode(3);
    root -> next -> next -> next = new ListNode(4);
    cout << "Detect Cycle 1: " << detectCycle(root) << endl;
    root -> next -> next -> next = root -> next;
    cout << "Detect Cycle 2: " << detectCycle(root) << endl;

    return 0;
}