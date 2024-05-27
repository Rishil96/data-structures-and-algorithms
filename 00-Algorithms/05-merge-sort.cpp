#include <iostream>
#include <vector>
using namespace std;

void print(vector<int> arr) {
    for (auto a: arr) cout << a << " ";
    cout << endl;
}

void merge(vector<int>& arr, int start, int end) {
    // Step 1: Get both the subarrays to merge
    int mid = start + (end - start) / 2;

    // Create subarrays
    vector<int> leftArray(mid - start + 1, 0);
    vector<int> rightArray(end - mid, 0);

    // Fill both subarrays
    int j = 0;
    for (int i=start; i<=mid; i++) leftArray[j++] = arr[i];
    j = 0;
    for (int i=mid+1; i<=end; i++) rightArray[j++] = arr[i];

    // Step 2: Initialize variables to traverse subarrays and write in main array
    int mainIndex = start;
    int leftIndex = 0;
    int rightIndex = 0;

    // Step 3: Merge 2 sorted arrays algorithm
    while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) {
        if (leftArray[leftIndex] < rightArray[rightIndex]) {
            arr[mainIndex++] = leftArray[leftIndex++];
        }
        else {
            arr[mainIndex++] = rightArray[rightIndex++];
        }
    }

    while (leftIndex < leftArray.size()) {
        arr[mainIndex++] = leftArray[leftIndex++];
    }

    while (rightIndex < rightArray.size()) {
        arr[mainIndex++] = rightArray[rightIndex++];
    }

    return ;
}

void mergeSort(vector<int>& arr, int start, int end) {
    // Base Case: Already sorted if single or no element
    if (start >= end) return ;
    // Ek Case:
    int mid = start + (end - start)/2;
    // Merge Sort on Left Subarray
    mergeSort(arr, start, mid);
    // Merge Sort on Right Subarray
    mergeSort(arr, mid + 1, end);
    // Merge back
    merge(arr, start, end);
}

int main() {

    vector<int> a1{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> a2{5, 10, 9, 4, 3, 8, 7, 2, 1, 6};
    vector<int> a3{100, 10, 20, 90, 80, 30, 40, 70, 60, 50};

    mergeSort(a1, 0, a1.size()-1);
    print(a1);

    mergeSort(a2, 0, a2.size()-1);
    print(a2);

    mergeSort(a3, 0, a3.size()-1);
    print(a3);

    return 0;
}