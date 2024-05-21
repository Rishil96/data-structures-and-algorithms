#include <iostream>
#include <vector>
using namespace std;

int binarySearch(vector<int> arr, int target) {
    int start = 0;
    int end = arr.size() - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] > target) {
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    return -1;
}

int main() {

    vector<int> arr{1, 2, 5, 7, 9, 12, 14, 18, 31};
    cout << "Binary Search 1: " << binarySearch(arr, 14) << endl;
    cout << "Binary Search 2: " << binarySearch(arr, 1) << endl;
    cout << "Binary Search 3: " << binarySearch(arr, 31) << endl;
    cout << "Binary Search 4: " << binarySearch(arr, 40) << endl;

    return 0;
}