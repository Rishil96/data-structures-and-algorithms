#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// 36. Minimum number of removals to make mountain array
/* 
    Another way to think is to find the maximum size mountain array from the given array which will involve removing least number of elements 
*/
int lengthOfLIS(vector<int>& nums, vector<int>& lis) {
    vector<int> ans;
    ans.push_back(nums[0]);         // Add first element in output lis
    lis.push_back(1);               // For first element size of lis is 1

    for (int i=1; i<nums.size(); i++) {
        // If curr num is greater than last element of lis, add it in ans
        if (ans.back() < nums[i]) {
            ans.push_back(nums[i]);
            lis.push_back(ans.size());
        }
        // Add current num in place of num just higher than it in ans array
        else {
            int index = lower_bound(ans.begin(), ans.end(), nums[i]) - ans.begin();
            ans[index] = nums[i];
            lis.push_back(index+1);
        }
    }
    return ans.size();
}

int minimumMountainRemovals(vector<int>& nums) {
    // Step 1: Find LIS and LDS for nums array
    vector<int> lis, lds;
    lengthOfLIS(nums, lis);
    reverse(nums.begin(), nums.end());
    lengthOfLIS(nums, lds);

    int largestMountain = INT_MIN;
    for (int i=0; i<nums.size(); i++) {
        // If LIS or LDS of current index is 1, it means current index is mountain peak so it doesn't have anything on its left/right
        if (lis[i] == 1 || lds[nums.size() - i - 1] == 1) continue;
        int ans = lis[i] + lds[nums.size()-i-1] - 1;
        largestMountain = max(ans, largestMountain);
    }

    return nums.size() - largestMountain;       
}


// 37. Make Array Strictly increasing
#define INF (1e9 + 1)

int maiRec(vector<int>& arr1, vector<int>& arr2, int prev, int i) {
    // Base Case
    if (i >= arr1.size()) return 0;

    // Ek Case
    // Exclude Case: If prev is smaller than current, simply ignore and move ahead
    int exclude = INF;
    if (prev < arr1[i]) {
        exclude = 0 + maiRec(arr1, arr2, arr1[i], i + 1);
    }

    // Include Case: Replace current with a number greater than previous whether actual current is greater than previous or not
    int include = INF;
    auto it = upper_bound(arr2.begin(), arr2.end(), prev);
    if (it != arr2.end()) {
        int index = it - arr2.begin();
        include = 1 + maiRec(arr1, arr2, arr2[index], i + 1);
    }

    return min(exclude, include);
}

int maiMem(vector<int>& arr1, vector<int>& arr2, int prev, int i, map<pair<int, int>, int> &dp) {
    // Base Case
    if (i >= arr1.size()) return 0;

    // DP Case
    if (dp.find({prev, i}) != dp.end()) return dp[{prev, i}];

    // Ek Case
    // Exclude Case: If prev is smaller than current, simply ignore and move ahead
    int exclude = INF;
    if (prev < arr1[i]) {
        exclude = 0 + maiMem(arr1, arr2, arr1[i], i + 1, dp);
    }

    // Include Case: Replace current with a number greater than previous whether actual current is greater than previous or not
    int include = INF;
    auto it = upper_bound(arr2.begin(), arr2.end(), prev);
    if (it != arr2.end()) {
        int index = it - arr2.begin();
        include = 1 + maiMem(arr1, arr2, arr2[index], i + 1, dp);
    }

    return dp[{prev, i}] = min(exclude, include);
}

int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
    // Sort 2nd array
    sort(arr2.begin(), arr2.end());

    // Recursion Solution
    /*
    int ans = maiRec(arr1, arr2, -1, 0);
    return ans != INF ? ans : -1;
    */

    // Memoization Solution
    map<pair<int, int>, int> dp;
    int ans = maiMem(arr1, arr2, -1, 0, dp);
    return ans != INF ? ans : -1;
}


// 38.


// 39.


// 40.



int main() {

    

    return 0;
}