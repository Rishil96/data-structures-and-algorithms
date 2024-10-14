#include <iostream>
#include <vector>
using namespace std;


// 1. Coin Change
int ccRecursion(vector<int>& coins, int amount) {
    // Base Case
    if (amount == 0) return 0;
    if (amount < 0) return INT_MAX;

    // Ek Case
    int minCoins = INT_MAX;

    // Try subtracting using all coins
    for (auto c: coins) {
        int currAns = ccRecursion(coins, amount - c);
        if (currAns != INT_MAX && currAns != -1) {
            minCoins = min(minCoins, currAns + 1);
        }
    }

    return minCoins == INT_MAX ? -1 : minCoins;
}

int ccMem(vector<int>& coins, int amount, vector<int>& dp) {
    // Base Case
    if (amount == 0) return 0;
    if (amount < 0) return INT_MAX;

    // DP Case
    if (dp[amount] != -1) return dp[amount];

    // Ek Case
    int minCoins = INT_MAX;

    // Try subtracting using all coins
    for (auto c: coins) {
        int currAns = ccMem(coins, amount - c, dp);
        if (currAns != INT_MAX && currAns != -1) {
            minCoins = min(minCoins, currAns + 1);
        }
    }

    dp[amount] = minCoins;
    return dp[amount];
}

int ccTab(vector<int>& coins, int amount) {
    // Step 1: Create DP Array
    vector<int> dp(amount + 1, INT_MAX);

    // Step 2: Fill Base Case answer
    dp[0] = 0;

    // Step 3: Reverse the top down approach to bottom up
    for (int a=1; a<=amount; a++) {
        int minCoins = INT_MAX;

        for (auto c: coins) {
            if (a - c >= 0) {
                int currAns = dp[a - c];
                if (currAns != INT_MAX) {
                    minCoins = min(minCoins, currAns + 1);
                }
            }
        }

        dp[a] = minCoins;
    }
    return dp[amount] != INT_MAX ? dp[amount] : -1;
}

int coinChange(vector<int>& coins, int amount) {
    // Memoization Solution
    /*
    vector<int> dp(amount + 1, -1);
    int ans = ccMem(coins, amount, dp);
    return ans == INT_MAX ? -1 : ans;
    */
    // Tabulation Solution
    return ccTab(coins, amount);
}


// 2. House Robber
int robRec(vector<int>& nums, int i) {
    // Base Case
    if (i >= nums.size()) return 0;

    // Ek Case
    // Rob
    int include = robRec(nums, i + 2) + nums[i];
    // Don't Rob
    int exclude = robRec(nums, i + 1) + 0;

    return max(include, exclude);
}

int robMem(vector<int>& nums, int i, vector<int>& dp) {
    // Base Case
    if (i == 0) return nums[i];
    if (i < 0) return 0;

    // DP Case
    if (dp[i] != -1) return dp[i];

    // Ek Case
    int include = robMem(nums, i - 2, dp) + nums[i];
    int exclude = robMem(nums, i - 1, dp) + 0;

    dp[i] = max(include, exclude);
    return dp[i];
}

int robTab(vector<int>& nums) {
    // Step 1: Create DP Array
    vector<int> dp(nums.size() + 1, 0);

    // Step 2: Add base case from Recursion
    dp[0] = nums[0];

    // Step 3: Bottom Up Approach
    for (int i=1; i<nums.size(); i++) {
        int include = nums[i];
        if (i - 2 >= 0)
            include += dp[i - 2];
        int exclude = dp[i - 1] + 0;

        dp[i] = max(include, exclude);
    }

    return dp[nums.size()-1];
} 

int robSO(vector<int>& nums) {
    // Step 1: Create variables for storing past data
    int prev2 = 0;
    int prev1 = 0;

    // Step 2: Loop through houses for robbery
    for (int i=0; i<nums.size(); i++) {
        int include = nums[i] + prev2;
        int exclude = prev1;

        int currAns = max(include, exclude);

        // Update variables
        prev2 = prev1;
        prev1 = currAns;
    }

    return prev1;
}

int rob(vector<int>& nums) {
    // Recursion Solution
    /*
    return robRec(nums, 0);
    */

    // Memoization Solution
    /*
    vector<int> dp(nums.size(), -1);
    return robMem(nums, nums.size()-1, dp);
    */

    // Tabulation Solution
    /*
    return robTab(nums);
    */

    // Space Optimization Solution
    return robSO(nums);
}


// 3.


// 4.


// 5.



int main() {
    

    return 0;
}