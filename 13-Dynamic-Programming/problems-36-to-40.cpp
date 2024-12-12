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


// 38. Burst Balloons
int mcRec(vector<int>& nums, int start, int end) {
    // Base Case
    if (start > end) return 0;

    // Ek Case
    int maxCoins = INT_MIN;

    /*
    Reverse Approach:-
        assume that the first balloon we burst is actually the last balloon left and we are bursting the balloons from last to first
        For first case, we assume to burst all balloons once but since we are assuming it to be the last balloon, we use the boundaries as the left and right of it instead of its neighbour
    */
    for (int i=start; i<=end; i++) {
        int burstCurrent = nums[start - 1] * nums[i] * nums[end + 1];
        int burstLeft = mcRec(nums, start, i - 1);
        int burstRight = mcRec(nums, i + 1, end);
        int currResult = burstCurrent + burstLeft + burstRight;
        maxCoins = max(maxCoins, currResult);
    }

    return maxCoins;
}

int mcMem(vector<int>& nums, int start, int end, vector<vector<int>> &dp) {
    // Base Case
    if (start > end) return 0;

    // DP Case
    if (dp[start][end] != -1) return dp[start][end];

    // Ek Case
    int maxCoins = INT_MIN;

    for (int i=start; i<=end; i++) {
        int burstCurrent = nums[start - 1] * nums[i] * nums[end + 1];
        int burstLeft = mcMem(nums, start, i - 1, dp);
        int burstRight = mcMem(nums, i + 1, end, dp);
        int currResult = burstCurrent + burstLeft + burstRight;
        maxCoins = max(maxCoins, currResult);
    }

    return dp[start][end] = maxCoins;
} 

int maxCoins(vector<int>& nums) {
    // Insert 1 numbered balloons at start and end
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    // Recursion Solution
    /*
    return mcRec(nums, 1, nums.size() - 2);
    */
    // Memoization Solution
    vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), -1));
    return mcMem(nums, 1, nums.size() - 2, dp);
}


// 39. Stone Game
bool stoneGame(vector<int>& piles) {
    // Since Alice can always pick first and the bigger of the pile, there will be atleast 1 way by which Alice will win
    return true;
}


// 40. Stone Game 2
int sg2Rec(vector<int>& piles, int start, int M, bool alice) {
    // Base Case
    if (start >= piles.size()) return 0;

    // Ek Case
    int points = 0;        
    int ans = alice ? INT_MIN : INT_MAX;
    
    for (int X=1; X<=2*M; X++) {
        // Handle index out of bounds
        if (X - 1 + start >= piles.size()) break;

        // Since we only need to get scores of Alice, only add stones during Alice's turn
        if (alice)
            points += piles[X + start - 1];

        // Get recursion answer
        int currAns = points + sg2Rec(piles, X + start, max(M, X), !alice);
        // Try to maximize alice's score
        if (alice) ans = max(ans, currAns);
        // Try to minimize bob's score
        else ans = min(ans, currAns);
    }

    return ans;
}

int sg2Mem(vector<int>& piles, int start, int M, bool alice, vector<vector<vector<int>>> &dp) {
    // Base Case
    if (start >= piles.size()) return 0;

    // DP Case
    if (dp[start][M][alice] != -1) return dp[start][M][alice];

    // Ek Case
    int points = 0;        
    int ans = alice ? INT_MIN : INT_MAX;
    
    for (int X=1; X<=2*M; X++) {
        // Handle index out of bounds
        if (X - 1 + start >= piles.size()) break;

        // Since we only need to get scores of Alice, only add stones during Alice's turn
        if (alice)
            points += piles[X + start - 1];

        // Get recursion answer
        int currAns = points + sg2Mem(piles, X + start, max(M, X), !alice, dp);
        // Try to maximize alice's score
        if (alice) ans = max(ans, currAns);
        // Try to minimize bob's score
        else ans = min(ans, currAns);
    }

    return dp[start][M][alice] = ans;
}

int stoneGameII(vector<int>& piles) {
    int M = 1;
    // Recursion Solution
    /*
    return sg2Rec(piles, 0, M, true);
    */

    // Memoization Solution
    vector<vector<vector<int>>> dp(piles.size(), vector<vector<int>>(piles.size()+1, vector<int>(2, -1)));
    return sg2Mem(piles, 0, M, true, dp);
}


// 41.



int main() {

    

    return 0;
}