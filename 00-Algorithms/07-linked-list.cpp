#include <iostream>
using namespace std;

// Linked List Node
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


// Linked List Class
class LinkedList
{
    ListNode* head;
    ListNode* tail;
    int size;

    public:
        // Init empty list
        LinkedList() {
            this -> head = NULL;
            this -> tail = NULL;
            size = 0;
        }

        // Init List with 1 element
        LinkedList(int val) {
            this -> head = new ListNode(val);
            this -> tail = head;
            size = 1;
        }

        // Print List
        void print() {
            cout << "*****\n" << "LINKED LIST :- ";
            ListNode* temp = head;
            while (temp) {
                cout << temp -> val << " ";
                temp = temp -> next;
            }
            cout << "\nHEAD :- " << head -> val << endl;
            cout << "TAIL :- " << tail -> val;
            cout << endl << "LENGTH :- " << this -> size << "\n*****" << endl;
        }

        // Get length
        int length() {
            return this -> size;
        }

        // Insert (beginning, middle, end)
        void insertAtHead(int val) {
            // Create the node that we will insert
            ListNode* newNode = new ListNode(val);

            // Case 1: Empty list
            if (head == NULL) {
                head = newNode;
                tail = head;
                size++;
                return ;
            }

            // Case 2: List with atleast one element
            newNode -> next = head;
            head = newNode;
            size++;

            return ;
        }

        void insertAtTail(int val) {
            // Create the node that we will insert
            ListNode* newNode = new ListNode(val);

            // Case 1: Empty list
            if (head == NULL) {
                head = newNode;
                tail = head;
                size++;
                return ;
            }

            // Case 2: List with atleast one element
            tail -> next = newNode;
            tail = newNode;
            size++;

            return ;
        }

        void insertAtPosition(int val, int pos) {
            // We will use 0 based index meaning head is 0th position and tail is size - 1 position.
            if (pos < 0 || pos > size) {
                cout << "INVALID INDEX" << endl;
                return ;
            }

            // Case 1: Handle beginning
            if (pos == 0) {
                insertAtHead(val);
                return ;
            }
            // Case 2: Handle ending
            else if (pos == size) {
                insertAtTail(val);
                return ;
            }
            // Case 3: Handle position
            ListNode* temp = head;
            ListNode* newNode = new ListNode(val);

            while (--pos) {
                temp = temp -> next;
            }

            newNode -> next = temp -> next;
            temp -> next = newNode;
            size++;

            return ;
        }

        // Delete (beginning, middle, end)
        void deleteFromHead() {
            // Case 1: Empty List
            if (head == NULL) {
                cout << "LIST IS ALREADY EMTPY" << endl;
                return ;
            }

            // Case 2: Single Element in List
            if (head == tail) {
                head = NULL;
                tail = NULL;
                size--;
                return ;
            }

            // Case 3: Multiple elements in List
            ListNode* deleteNode = head;
            head = head -> next;
            delete deleteNode;
            size--;
            return ;
        }

        void deleteFromTail() {
            // Case 1: Empty List
            if (head == NULL) {
                cout << "LIST IS ALREADY EMPTY" << endl;
                return ;
            }

            // Case 2: Single element in List
            if (head == tail) {
                head = NULL;
                tail = NULL;
                size--;
                return ;
            }

            // Case 3: Multiple element in List
            ListNode* temp = head;
            ListNode* deleteNode = tail;
            while (temp -> next != tail) {
                temp = temp -> next;
            }

            temp -> next = NULL;
            tail = temp;
            delete deleteNode;
            size--;
            return ;
        }

        void deleteFromPosition(int pos) {
            // Case 1: Invalid Position
            if (pos < 0 || pos >= size) {
                cout << "INVALID POSITION" << endl;
                return ;
            }

            // Case 2: Head position
            if (pos == 0) {
                deleteFromHead();
                return ;
            }

            // Case 3: Tail position
            if (pos == size - 1) {
                deleteFromTail();
                return ;
            }

            // Case 4: Middle Position
            ListNode* temp = head;
            while (--pos) {
                temp = temp -> next;
            }
            ListNode* deleteNode = temp -> next;
            temp -> next = deleteNode -> next;
            delete deleteNode;
            size--;
            return ;

        }

        // Search in a Linked List
        bool search(int key) {
            ListNode* temp = head;
            while (temp) {
                if (temp -> val == key) return 1;
                temp = temp -> next;
            }

            return 0;
        }

        // Reverse a Linked List
        void reverseList() {
            // Step 1: Init variables needed for reverse
            ListNode* prevNode = NULL;
            ListNode* currNode = head;

            // Step 2: Set head as the new tail of the list
            tail = head;

            // Step 3: Reverse the list
            while (currNode) {
                ListNode* nextNode = currNode -> next;
                currNode -> next = prevNode;
                prevNode = currNode;
                currNode = nextNode;
            }

            // Step 4: Set the new head of the list
            head = prevNode;

            return ;
        }

};



int main() {

    LinkedList l1;

    l1.deleteFromHead();

    l1.insertAtHead(50);
    l1.insertAtHead(40);
    l1.insertAtHead(30);
    l1.insertAtHead(20);
    l1.insertAtHead(10);

    l1.print();

    l1.insertAtTail(60);
    l1.insertAtTail(70);
    l1.insertAtTail(80);
    l1.insertAtTail(90);
    l1.insertAtTail(100);

    l1.print();

    l1.insertAtPosition(55, 5);
    l1.insertAtPosition(0, 0);
    l1.insertAtPosition(110, l1.length());
    l1.insertAtPosition(5, 1);
    l1.insertAtPosition(105, 13);
    l1.insertAtPosition(-1, -1);
    l1.insertAtPosition(120, 17);

    l1.print();

    l1.deleteFromHead();
    l1.deleteFromHead();

    l1.print();

    l1.deleteFromTail();
    l1.deleteFromTail();

    l1.print();

    l1.deleteFromPosition(5);
    l1.deleteFromPosition(l1.length() - 1);
    l1.deleteFromPosition(0);

    l1.print();

    cout << "SEARCH IN LINKED LIST 10 :- " << l1.search(10) << endl;
    cout << "SEARCH IN LINKED LIST 50 :- " << l1.search(50) << endl;
    cout << "SEARCH IN LINKED LIST 100 :- " << l1.search(100) << endl;

    l1.reverseList();

    l1.print();

    l1.reverseList();

    l1.print();

    return 0;
}