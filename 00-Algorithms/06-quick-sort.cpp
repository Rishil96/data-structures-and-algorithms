#include <iostream>
#include <vector>
using namespace std;


void print(vector<int> arr) {
    for (auto a: arr) cout << a << " ";
    cout << endl;
}

int partition(vector<int>& arr, int start, int end) {
    // Step 1: Set pivot index and element to first element of array
    int pivot = start;
    int pivotElement = arr[pivot];

    // Step 2: Find the correct position of pivotElement in the array and place it there
    int count = 0;
    for (int i=start+1; i<=end; i++) {
        if (arr[i] < pivotElement) count++;
    }

    swap(arr[pivot], arr[start + count]);
    pivot = start + count;
    pivotElement = arr[pivot];

    // Step 3: Move all elements smaller than pivot to its left and elements larger than pivot to its right
    int left = start;
    int right = pivot + 1;

    while (right <= end) {
        if (arr[right] < pivotElement) {
            swap(arr[left++], arr[right]);
        }
        else right++;
    }

    return pivot;
}

void quickSort(vector<int>& arr, int start, int end) {
    // Base Case
    if (start >= end) return ;

    // Ek Case
    int pivotIndex = partition(arr, start, end);

    // Split left and right subarrays excluding partition index
    quickSort(arr, start, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, end);

    return ;
}

int main() {

    vector<int> a1{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> a2{5, 10, 9, 4, 3, 8, 7, 2, 1, 6};
    vector<int> a3{100, 10, 20, 90, 80, 30, 40, 70, 60, 50};
    vector<int> a4{5, 5, 5, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 1, 7, 7, 7, 8, 8, 10, 11, 10, 9, 9};

    quickSort(a1, 0, a1.size()-1);
    print(a1);

    quickSort(a2, 0, a2.size()-1);
    print(a2);

    quickSort(a3, 0, a3.size()-1);
    print(a3);

    quickSort(a4, 0, a4.size()-1);
    print(a4);


    return 0;
}