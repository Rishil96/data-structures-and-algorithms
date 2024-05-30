#include <iostream>
#include <vector>
using namespace std;

class Queue
{
    int *arr;
    int front, rear;
    int size;

    public:
    Queue(int size) {
        arr = new int[size];
        front = -1;
        rear = 0;
        this -> size = size;
    }

    // Enqueue
    bool enqueue(int data) {
        // Queue Overflow
        if (rear == size) {
            cout << "QUEUE OVERFLOW" << endl;
            return false;
        }

        // First element in queue
        if (front == -1) {
            front++;
        }

        arr[rear] = data;
        rear++;
        return true;
    } 

    // Dequeue
    int dequeue() {
        // Queue Underflow
        if (front == -1) {
            cout << "QUEUE UNDERFLOW" << endl;
            return -1;
        }

        // Pop
        int popped = arr[front];
        arr[front] = 0;
        front++;
        if (front == rear) {
            front = -1;
            rear = 0;
        }

        return popped;
    }

    // Peek
    int peek() {
        return front == -1 ? front : arr[front];
    }

    // Size
    int getSize() {
        return front != -1 ? rear - front : 0;
    }

    // Empty
    bool empty() {
        return front == -1;
    }

    // Print
    void print() {
        cout << "******\n";
        cout << "FRONT :- " << front << endl;
        cout << "REAR :- " << rear << endl;
        cout << "QUEUE :- ";
        for (int i=front; (i<rear) && (i != -1); i++) {
            cout << arr[i] << " ";
        }
        cout << "\n******" << endl;
    }
};

int main() {

    Queue q(10);
    q.print();
    cout << "Size :- " << q.getSize() << endl;
    q.dequeue();

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);

    q.print();
    cout << "Size :- " << q.getSize() << endl;

    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    q.enqueue(9);
    q.enqueue(10);
    q.enqueue(11);

    q.print();
    cout << "Size :- " << q.getSize() << endl;

    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;
    cout << "Dequeue :- " << q.dequeue() << endl;

    q.print();
    cout << "Size :- " << q.getSize() << endl;

    return 0;
}