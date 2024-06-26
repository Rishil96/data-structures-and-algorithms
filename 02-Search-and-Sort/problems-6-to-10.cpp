#include <iostream>
#include <vector>
using namespace std;


// 6. Search in a rotated and sorted array
// Binary Search
int bs(vector<int>& nums, int left, int right, int &target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    // Handle Single element in array
    if (left == right && nums[left] == target) return 0;
    else if (left == right && nums[left] != target) return -1;

    // Find the rotation point using Binary Search algorithm
    while (left < right) {
        // Calculate mid and check if our target is present on mid by any chance
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;

        // mid element is greater than or equal to the 0th element, means we are to the left of rotation point
        if (nums[mid] >= nums[0]) {
            left = mid + 1;
        }
        // mid element is less than 0th element, it means we are on the right side of array's rotation point
        else right = mid;
    }
    // Find target on respective subarrays using Binary Search
    if (right - 1 >= 0 && target >= nums[0] && target <= nums[right-1]) return bs(nums, 0, right-1, target);
    else return bs(nums, right, nums.size()-1, target);
}


// 7. Search in a rotated and sorted array 2
bool ls(vector<int>& nums, int target) {
    for (auto n: nums) if (n == target) return true;
    return false;
}

bool search2(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    // Handle Single element in array
    if (left == right && nums[left] == target) return true;
    else if (left == right && nums[left] != target) return false;

    // Find the rotation point using Binary Search algorithm
    while (left < right) {
        // Calculate mid and check if our target is present on mid by any chance
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return true;

        // mid element is greater than or equal to the 0th element, means we are to the left of rotation point
        if (nums[mid] >= nums[0]) {
            left = mid + 1;
        }
        // mid element is less than 0th element, it means we are on the right side of array's rotation point
        else right = mid;
    }
    // Find target on respective subarrays using Binary Search and if not found, also try Linear Search due to duplicates Binary Search won't work in edge cases
    if (right - 1 >= 0 && target >= nums[0] && target <= nums[right-1] && bs(nums, 0, right-1, target)) return true;
    else if (bs(nums, right, nums.size()-1, target)) return true;
    else return ls(nums, target);
}


// 8. Square root of a number using Binary Search
int mySqrt(int x) {
    long long left = 0;
    long long right = x;
    long long ans = left;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (mid * mid <= x) {
            ans = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return ans;
}


// 9. Binary Search in a 2D Matrix
bool bs2(vector<int>& arr, int s, int e, int &target) {
    while (s <= e) {
        int mid = s + (e - s) / 2;
        if (arr[mid] == target) return true;
        else if (arr[mid] < target) s = mid + 1;
        else e = mid - 1;
    }
    return false;
}

int matSearch(vector <vector <int>> &mat, int N, int M, int X)
{
    // your code here
    int start = 0;
    int end = M - 1;
    
    for (auto arr: mat) {
        if (arr[0] <= X && arr.back() >= X) {
            int ans = bs2(arr, start, end, X);
            if (ans) return 1;
        }
    }
    
    return 0;
}


int main() {

    

    return 0;
}