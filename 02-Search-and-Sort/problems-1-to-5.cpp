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


// 4. Find the missing number in a sorted array
int missingNumber(vector<int> &nums) {
    // Use left and right pointers for Binary Search
    int left = 0;
    int right = nums.size() - 1;

    // Binary Search
    while (left < right) {
        // Get mid
        int mid = left + (right - left)/2;
        // We are on left side of missing element
        if (nums[mid] == mid + 1) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return (nums[right] == right + 1) ? right + 2 : right + 1;
}


// 5. Peak element in a mountain array
int peakIndexInMountainArray(vector<int>& arr) {
    // Variables to implement Binary Search
    int left = 0;
    int right = arr.size() - 1;

    // Binary Search logic
    while (left < right) {
        int mid = left + (right - left) / 2;

        // We are on left of peak
        if (mid + 1 < arr.size() && arr[mid] <= arr[mid + 1]) {
            left = mid + 1;
        }
        // We are either on the peak element or to the right of peak
        else right = mid;
    }

    return right;
}


int main() {

    vector<int> nums{1, 2, 3, 4, 5, 5, 5, 6, 6, 7, 7, 8};
    cout << "Total Occurrences 1: " << totalOccurrences(nums, 5) << endl;
    cout << "Total Occurrences 2: " << totalOccurrences(nums, 9) << endl;

    vector<int> nums2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "Missing Number: " << missingNumber(nums2) << endl;

    return 0;
}