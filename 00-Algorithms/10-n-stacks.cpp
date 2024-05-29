#include <iostream>
#include <vector>
using namespace std;

class NStack
{
    int *a, *top, *next;
    int n;
    int size;
    int freeSpot;

    public:
    NStack(int _n, int _s) : n(_n), size(_s) {
        freeSpot = 0;
        a = new int[size];
        top = new int[n];
        next = new int[size];

        for (int i=0; i<n; i++) top[i] = -1;
        for (int i=0; i<size; i++) next[i] = i + 1;
        next[size - 1] = -1;
    } 

    bool push(int x, int m) {
        // Check overflow
        if (freeSpot == -1) return false;

        // Step 1: Get free spot
        int index = freeSpot;

        // Step 2: Update free spot
        freeSpot = next[index];

        // Step 3: Insert element in array
        a[index] = x;

        // Step 4: Update next array
        next[index] = top[m - 1];

        // Step 5: Update top array
        top[m - 1] = index;

        return true;
    }

    int pop(int m) {
        // Stack underflow
        if (top[m - 1] == -1) return -1;

        // Step 1: Get index of top
        int index = top[m - 1];

        // Step 2: Update top array
        top[m - 1] = next[index];

        // Step 3: Pop
        int popped = a[index];

        // Step 4: Update next array
        next[index] = freeSpot;

        // Step 5: Update freespot using index from which top was popped
        freeSpot = index;

        return popped;
    }

    ~NStack() {
        delete[] a;
        delete[] top;
        delete[] next;
    }
};


int main() {

    NStack st(3, 6);
    cout << st.push(10, 1) << endl;
    cout << st.pop(1) << endl;
    cout << st.push(10, 1) << endl;
    cout << st.push(20, 2) << endl;
    cout << st.push(30, 3) << endl;
    cout << st.push(40, 1) << endl;
    cout << st.push(50, 2) << endl;
    cout << st.push(60, 2) << endl;
    cout << st.push(70, 1) << endl;
    cout << st.pop(1) << endl;
    cout << st.pop(1) << endl;
    cout << st.pop(2) << endl;
    cout << st.pop(2) << endl;
    cout << st.pop(2) << endl;
    cout << st.pop(3) << endl;
    cout << st.pop(3) << endl;

    return 0;
}