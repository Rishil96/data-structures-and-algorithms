#include <iostream>
#include <vector>
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


// 37.


// 38.


// 39.


// 40.



int main() {

    

    return 0;
}