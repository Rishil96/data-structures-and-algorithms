#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int> &arr) {
    for (int pos=0; pos<arr.size()-1; pos++) {
        int smallest = pos;
        for (int i=pos+1; i<arr.size(); i++) {
            if (arr[smallest] > arr[i]) smallest = i;
        }

        swap(arr[pos], arr[smallest]);
    }
}

int main() {

    vector<int> arr{20, 19, 18, 17, 16, 55, 54, 53, 52, 51};
    vector<int> arr2{1, 6, 2, 7, 3, 8, 4, 9, 5, 10};
    vector<int> arr3{10, 30, 90, 100, 80, 70, 60, 20, 40, 50};

    selectionSort(arr);
    cout << "Selection Sort 1: ";
    for (int i=0; i<arr.size(); i++) {
        cout << arr[i] << " ";
    }

    selectionSort(arr2);
    cout << "\nSelection Sort 2: ";
    for (int i=0; i<arr2.size(); i++) {
        cout << arr2[i] << " ";
    }

    selectionSort(arr3);
    cout << "\nSelection Sort 3: ";
    for (int i=0; i<arr3.size(); i++) {
        cout << arr3[i] << " ";
    }

    return 0;
}