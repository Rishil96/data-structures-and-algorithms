#include <iostream>
using namespace std;

class Stack
{
    int *arr;
    int capacity;
    int top;

    public:
        Stack(int capacity) {
            this -> capacity = capacity;
            arr = new int[capacity];
            top = -1;
        }

        // Push
        bool push(int data) {
            // Stack overflow case
            if (top == capacity - 1) {
                cout << "STACK OVERFLOW" << endl;
                return false;
            }

            // Normal case
            top++;
            arr[top] = data;
            return true;
        }

        // Pop
        int pop() {
            // Stack Underflow case
            if (top == -1) {
                cout << "STACK UNDERFLOW" << endl;
                return -1;
            }

            // Regular case
            int popped = arr[top];
            arr[top--] = 0;
            return popped;
        }

        // Peek
        int peek() {
            return (top == -1) ? top : arr[top];
        }

        // Size
        int size() {
            return top + 1;
        }

        // Empty
        bool empty() {
            return top == -1;
        }

        // Print Stack
        void print() {
            cout << "******" << endl;
            cout << "STACK :- ";
            for (int i=0; i<=top; i++) cout << arr[i] << " ";
            cout << "\n******" << endl;
            return ;
        }
};

int main() {

    Stack st(10);
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    
    st.print();
    cout << "Peek: " << st.peek() << endl;
    cout << "Size: " << st.size() << endl;
    cout << "Empty: " << st.empty() << endl;

    st.push(6);
    st.push(7);
    st.push(8);
    st.push(9);
    st.push(10);
    st.push(11);

    st.print();
    cout << "Peek: " << st.peek() << endl;
    cout << "Size: " << st.size() << endl;
    cout << "Empty: " << st.empty() << endl;

    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;
    cout << "Pop: " << st.pop() << endl;

    st.print();
    cout << "Peek: " << st.peek() << endl;
    cout << "Size: " << st.size() << endl;
    cout << "Empty: " << st.empty() << endl;

    return 0;
}