#include <iostream>
using namespace std;

class KQueue
{
    public:
    int n, k, freeSpot;
    int *arr, *front, *rear, *next;

    KQueue(int _n, int _k) : n(_n), k(_k) {
        arr = new int[n];
        next = new int[n];
        front = new int[k];
        rear = new int[k];
        freeSpot = 0;

        for (int i=0; i<k ;++i) {
            front[i] = rear[i] = -1;
        }

        for (int i=0; i<n; i++) {
            next[i] = i + 1;
        }
        next[n - 1] = -1;
    }

    // Push X into ith queue
    bool push(int x, int qi) {
        // Check overflow
        if (freeSpot == -1) return false;

        // 1. Find free index
        int index = freeSpot;

        // 2. Update free spot
        freeSpot = next[index];

        // 3. If first element in qi
        if (front[qi] == -1) {
            front[qi] = index;
        }
        // 4. Link previous rear to current rear
        else {
            next[rear[qi]] = index;
        }

        // 5. Update next
        next[index] = -1;

        // 6. Update rear
        rear[qi] = index;

        // 7. Insert element
        arr[index] = x;

        return true;
    }

    int pop(int qi) {
        // Check underflow
        if (front[qi] == -1) return -1;

        // 1. Find index
        int index = front[qi];

        // 2. Update front
        front[qi] = next[index];

        // 3. Manage freespot in next array
        next[index] = freeSpot;

        // 4. Update freespot
        freeSpot = index;

        // 5. Get element to pop
        int popped = arr[index];
        arr[index] = 0;
        return popped;
    }

};

int main() {

    KQueue q(8, 3);
    cout << q.push(1, 0) << endl;
    cout << q.push(2, 0) << endl;
    cout << q.push(5, 1) << endl;
    cout << q.push(3, 0) << endl;
    cout << q.pop(1) << endl;
    cout << q.pop(1) << endl;
    cout << q.pop(0) << endl;
    cout << q.pop(0) << endl;
    cout << q.pop(0) << endl;
    cout << q.pop(0) << endl;

    return 0;
}