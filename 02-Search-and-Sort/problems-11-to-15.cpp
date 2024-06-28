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


int main() {

    

    return 0;
}