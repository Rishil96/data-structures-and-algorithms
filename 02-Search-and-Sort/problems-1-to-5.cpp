#include <iostream>
#include <vector>
using namespace std;

// 1,2. First and Last Occurrence of an element in a sorted array
int lowerBound(vector<int>& nums, int target) {
    // Store answer
    int index = -1;

    // Create left and right indexes for Binary Search
    int left = 0;
    int right = nums.size() - 1;

    // Binary Search algorithm for lower bound
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            index = mid;
            right = mid - 1;
        }
        else if (nums[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return index;
}

int upperBound(vector<int>& nums, int target) {
    // Store answer
    int index = -1;

    // Left and right variables for Binary Search algorithm
    int left = 0;
    int right = nums.size() - 1;

    // Binary Search algorithm for upper bound
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            index = mid;
            left = mid + 1;
        }
        else if (nums[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return index;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int first = lowerBound(nums, target);
    int last = upperBound(nums, target);

    return vector<int> {first, last};
}


// 3. Total number of occurrences of target element
int totalOccurrences(vector<int>& nums, int target) {
    int ans = upperBound(nums, target) - lowerBound(nums, target);
    return  ans == 0 ? 0 : ans + 1;
}

int main() {

    vector<int> nums{1, 2, 3, 4, 5, 5, 5, 6, 6, 7, 7, 8};
    cout << "Total Occurrences 1: " << totalOccurrences(nums, 5) << endl;

    cout << "Total Occurrences 2: " << totalOccurrences(nums, 9) << endl;

    return 0;
}