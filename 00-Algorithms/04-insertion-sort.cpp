#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int> &arr) {
    for (int i=1; i<arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}


int main() {

    vector<int> arr{20, 19, 18, 17, 16, 55, 54, 53, 52, 51};
    vector<int> arr2{1, 6, 2, 7, 3, 8, 4, 9, 5, 10};
    vector<int> arr3{10, 30, 90, 100, 80, 70, 60, 20, 40, 50};

    insertionSort(arr);
    cout << "Insertion Sort 1: ";
    for (int i=0; i<arr.size(); i++) {
        cout << arr[i] << " ";
    }

    insertionSort(arr2);
    cout << "\nInsertion Sort 2: ";
    for (int i=0; i<arr2.size(); i++) {
        cout << arr2[i] << " ";
    }

    insertionSort(arr3);
    cout << "\nInsertion Sort 3: ";
    for (int i=0; i<arr3.size(); i++) {
        cout << arr3[i] << " ";
    }

    return 0;
}