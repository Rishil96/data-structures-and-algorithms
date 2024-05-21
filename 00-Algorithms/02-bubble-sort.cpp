#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int> &arr) {
    for (int i=0; i<arr.size()-1; i++) {
        bool swapped = false;
        for (int j=0; j<arr.size()-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

int main() {

    vector<int> arr{20, 19, 18, 17, 16, 55, 54, 53, 52, 51};
    vector<int> arr2{1, 6, 2, 7, 3, 8, 4, 9, 5, 10};
    vector<int> arr3{10, 30, 90, 100, 80, 70, 60, 20, 40, 50};

    bubbleSort(arr);
    cout << "Bubble Sort 1: ";
    for (int i=0; i<arr.size(); i++) {
        cout << arr[i] << " ";
    }

    bubbleSort(arr2);
    cout << "\nBubble Sort 2: ";
    for (int i=0; i<arr2.size(); i++) {
        cout << arr2[i] << " ";
    }

    bubbleSort(arr3);
    cout << "\nBubble Sort 3: ";
    for (int i=0; i<arr3.size(); i++) {
        cout << arr3[i] << " ";
    }

    return 0;
}