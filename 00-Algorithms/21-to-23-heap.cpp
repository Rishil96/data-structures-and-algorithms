#include <iostream>
using namespace std;

class Heap
{
    public:
        int *arr;
        int size;

        Heap(int size) {
            this -> size = -1;
            arr = new int[size];
            insert(-1);
        }

        void insert(int val) {
            // Step 1: Insert value at the end of array
            size++;
            int index = size;
            arr[index] = val;

            // Step 2: Compare with parent and swap till we find its correct position
            while (index > 1) {
                // Max Heap condition: if child is greater than parent swap them and update index
                if (arr[index] > arr[index / 2]) {
                    swap(arr[index], arr[index / 2]);
                    index /= 2;
                }
                else {
                    break;
                }
            }
        }

        int deleteTop() {
            // Step 0: Save top element before we overwrite/delete it
            int node = arr[1];

            // Step 1: Place last element on top
            arr[1] = arr[size--];

            // Step 2: Place new top element to its correct position
            int index = 1;
            while (index < size) {
                int leftIndex = index * 2;
                int rightIndex = leftIndex + 1;

                int largestIndex = index;

                // Compare with left and right child and get the largest element
                if (leftIndex < size && arr[largestIndex] < arr[leftIndex]) {
                    largestIndex = leftIndex;
                }

                if (rightIndex < size && arr[largestIndex] < arr[rightIndex]) {
                    largestIndex = rightIndex;
                }

                if (index == largestIndex) break;
                swap(arr[index], arr[largestIndex]);
                index = largestIndex;
            }

            return node;
        }

        void printHeap() {
            for (int i=0; i<=size; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
};


// Heapify: place element at index in an array to its correct position in terms of a heap
void heapify(int *arr, int n, int index) {
    int largest = index;
    int leftChild = index * 2;
    int rightChild = leftChild + 1;

    // Check if left child is greater than parent
    if (leftChild <= n && arr[largest] < arr[leftChild]) {
        largest = leftChild;
    }
    // Check if right child is greater than parent
    if (rightChild <= n && arr[largest] < arr[rightChild]) {
        largest = rightChild;
    }
    // Check if element at index was not placed at correct position
    if (largest != index) {
        swap(arr[index], arr[largest]);
        heapify(arr, n, largest);
    }

    return ;
}


// Build heap using an existing array
void buildHeap(int *arr, int n) {
    // To build a heap we heapify all non-leaf elements in the array
    for (int i=n/2; i>0; i--) {
        heapify(arr, n, i);
    }
}


// Heap Sort
void heapSort(int *arr, int n) {
    // 1 -> Save last index of array
    int index = n;

    // 2 -> Run loop for all indexes till index > 1
    while (index > 1) {
        // 3 -> Place first element to the end as in max heap first element is the largest.
        swap(arr[1], arr[index--]);
        // 4 -> Call heapify by ignoring the last index of the array as we are considering it sorted because we placed the largest element at the end above.
        heapify(arr, index, 1);
    }

    return ;
}


int main() {

    Heap h(100);
    h.insert(100);
    h.insert(50);
    h.insert(60);
    h.insert(40);
    h.insert(45);
    
    cout << "Printing Heap: ";
    h.printHeap();

    h.insert(110);
    cout << "Printing Heap: ";
    h.printHeap();

    h.deleteTop();
    cout << "Printing Heap: ";
    h.printHeap();

    h.deleteTop();
    cout << "Printing Heap: ";
    h.printHeap();


    return 0;
}