#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// 11. Single Unique element in an array of element pairs
int singleNonDuplicate(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        // Odd Case
        if (mid & 1) {
            // If mid element is equal to mid + 1 element, it means we are on right side of unique element
            if (mid + 1 < nums.size() && nums[mid] == nums[mid + 1]) {
                right = mid;
            }
            // Else we are on left side
            else {
                left = mid + 1;
            }
        }
        // Even Case
        else {
            // If mid element is equal to mid + 1 element, we are on left side of unique element
            if (mid + 1 < nums.size() && nums[mid] == nums[mid + 1]) {
                left = mid + 1;
            }
            // Else we are on right side
            else {
                right = mid;
            }
        }
    }

    return nums[right];
}


// 12. Find K diff pairs
int findPairs(vector<int>& nums, int k) {
    // Sort the input array
    sort(nums.begin(), nums.end());

    // Use 2 pointers to find all pairs
    int i = 0;
    int j = 1;

    // Store ans
    int ans = 0;

    // Run till both i and j are valid indexes of the array
    while (j < nums.size()) {
        // Calculate difference
        int difference = nums[j] - nums[i];
        // If difference is k, increment ans, i and j
        if (difference == k) {
            ans++;
            i++;
            j++;
        }
        // If difference is greater than k, reduce difference by incrementing i
        else if (difference > k) i++;
        // When difference is lesser than k, incread difference by incrementing j
        else j++;

        // To handle duplicate pairs, after one pair was processed, move i ahead till it is not a duplicate to its previous index i.e. i - 1
        while (i - 1 >= 0 && i < nums.size() && nums[i-1] == nums[i]) i++;

        // Reset j to i + 1 to again avoid duplicate pairs
        if (i >= j) j = i + 1;
    }

    return ans;
}


// 13. Find k closest elements
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int left = 0;
    int right = arr.size() - 1;
    
    // Store index of num closest to x
    int center = -1;

    // Find upper bound of x
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x) {
            center = mid;
            break;
        }
        else if (arr[mid] > x) {
            center = mid;
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }

    // Update center to right if it was not updated even once       
    center = (center == -1) ? right : center;

    if (center - 1 >= 0 && abs(arr[center-1]-x) <= abs(arr[center]-x)) {
        center = center - 1;
    }

    // Use left and right to set the range of vectors
    left = center;
    right = center;
    vector<int> ans;

    while (--k) {
        // Both left and right are valid
        if (left - 1 >= 0 && right + 1< arr.size()) {
            // Check which num is closer to x
            if (x - arr[left - 1] <= arr[right + 1] - x) {
                left--;
            }
            else {
                right++;
            }
        }
        // Only left is valid
        else if (left - 1 >= 0) {
            left--;
        }
        // Only right is valid
        else {
            right++;
        }
    }
    
    return vector<int>(arr.begin()+left, arr.begin()+right+1);
}


// 14. Exponential Search
int binarySearch(int arr[], int l, int r, int x) {
    if (r >= l)
    {
        int mid = l + (r - l)/2;
 
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then it
        // can only be present n left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid-1, x);
 
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid+1, r, x);
    }
 
    // We reach here when element is not present
    // in array
    return -1;
}

int exponentialSearch(int arr[], int n, int x) {
    // If x is present at first location itself
    if (arr[0] == x)
        return 0;
 
    // Find range for binary search by
    // repeated doubling
    int i = 1;
    while (i < n && arr[i] <= x)
        i = i*2;
 
    //  Call binary search for the found range.
    return binarySearch(arr, i/2, min(i, n-1), x);
}


// 15. Book Allocation Problem
bool canAllocate(int arr[], int &n, int &students, int &totalPages) {
    int allocated = 1;
    int currPages = 0;

    for (int i=0; i<n; i++) {
        int currBook = arr[i];

        // If curr book has more pages than our total pages limit, return false
        if (currBook > totalPages) return false;

        // Check if curr Book can be allocated to the current student where curr student has currPages already allocated
        if (currBook + currPages <= totalPages) {
            currPages += currBook;
        }
        // If curr book cannot be allocated to the current student, then allocate it to the next student
        else {
            allocated++;
            currPages = currBook;
        }
        // If all students already got their maximum assigned pages before going through all books, 
        // it means there are books still pending to be assigned so its an invalid answer
        if (allocated > students) return false;
    }

    // Here, we return true even though all students might not have book allocated because we are allocating more pages
    // to a single student so a valid allocation is definitely possible even though less students were assigned books as per condition.
    return allocated <= students;
}


long long findPages(int n, int arr[], int m) {
    // Base Case: If there are more students than books, every student won't have a book
    if (m > n) return -1;

    long long ans = -1;

    // Set search space for optimal number of pages to be alloted 0 to total pages
    int left = 0;
    int right = 0;

    for (int i=0; i<n; i++) right += arr[i];

    // Search for optimal answer
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if current pages (mid) is a valid allocation, if yes then save ans and try to reduce the pages
        if (canAllocate(arr, n, m, mid)) {
            ans = mid;
            right = mid - 1;
        }
        // If cannot be allocated, then increase the pages to find an answer
        else {
            left = mid + 1;
        }
    }

    return ans;
}


int main() {

    int n = 7;
    int arr[] = {15, 10, 19, 10, 5, 18, 7};
    int m = 5;

    cout << "Book Allocation: " << findPages(n, arr, m) << endl;

    return 0;
}