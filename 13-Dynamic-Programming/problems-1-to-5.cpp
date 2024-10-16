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


// 3. House Robber 2
int rob2Rec(vector<int>& nums, int i, int n) {
    // Base Case
    if (i > n) return 0;

    // Ek Case
    int include = rob2Rec(nums, i + 2, n) + nums[i];
    int exclude = rob2Rec(nums, i + 1, n) + 0;

    return max(include, exclude);
}

int rob2Mem(vector<int>& nums, int i, int &n, vector<vector<int>> &dp) {
    // Base Case
    if (i > n) return 0;

    // Dp Case
    if (dp[i][n] != -1) return dp[i][n];

    // Ek Case
    int include = rob2Mem(nums, i + 2, n, dp) + nums[i];
    int exclude = rob2Mem(nums, i + 1, n, dp) + 0;

    dp[i][n] = max(include, exclude);
    return dp[i][n];
}

int rob2(vector<int>& nums) {
    int n = nums.size() - 1;
    // Recursion Approach
    /*
    int rob1 = rob2Rec(nums, 1, n);
    n--;
    int rob2 = rob2Rec(nums, 0, n);
    return max(rob1, rob2);
    */

    // Memoization Approach
    if (nums.size() == 1) return nums[0];

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
    int rob1 = rob2Mem(nums, 1, n, dp);
    // dp.clear();
    n--;
    int rob2 = rob2Mem(nums, 0, n, dp);
    return max(rob1, rob2);
}


// 4. Painting Fences
const long long MOD = 1000000007; 

long long paintRec(int &n, int &k) {
    /*
        Base Case 1: 
            For 1 fence, there are k different colors using which we can paint it
    */
    if (n == 1) return k;
    /*
        Base Case 2: 
            For 2 fences, there are 2 possibilites:-
            Both fences are painted with same color and both fences are painted with different colors
            Same Color: k different ways e.g. ( if k = 3 and n = 2 the ways are -> RR GG BB <-)
            Different Color: k * (k - 1) ways e.g. (if k = 3 (RGB) and n = 2, the diff ways are -> RG RB BG BR GR GB <-)
            So, adding up same and different color ways will give us the total number of ways to paint 2 fences
    */ 
    if (n == 2) return k + (k * (k - 1));

    /*
        Recursive Case:
            Find previous 2 recursive solutions to build the current solution i.e. n - 2 and n - 1
    */
    n -= 2;
    long long ans1 = paintRec(n, k);
    n += 2;

    n -= 1;
    long long ans2 = paintRec(n, k);
    n += 1;

    /*
        Main Case:
            Formula to calculate different ways to paint n fences using previous 2 solutions.
    */
    long long finalAns = ((ans1 + ans2) * (k - 1)) % MOD;
    return finalAns;
}

long long paintMem(int &n, int &k, vector<int>& dp) {
    // Base Case
    if (n == 1) return k;
    if (n == 2) return k + (k * (k - 1));

    // DP Case
    if (dp[n] != -1) return dp[n];

    // Recursive Case
    n -= 2;
    long long ans1 = paintMem(n, k, dp);
    n += 2;
    
    n -= 1;
    long long ans2 = paintMem(n, k, dp);
    n += 1;

    dp[n] = ((ans1 + ans2) * (k - 1)) % MOD;
    return dp[n]; 
}

long long paintTab(int &n, int &k) {
    // Step 1: Create DP Array
    vector<int> dp(n + 1, 0);
    // Step 2: Add base cases from Memoization in DP Array
    dp[1] = k;
    dp[2] = k + (k * (k - 1));

    // Step 3: Bottom up loop
    for (int i=3; i<=n; i++) {
        // In this loop, i is mimicking n from Recursion
        long long ans1 = dp[i - 2];
        long long ans2 = dp[i - 1];
        long long finalAns = ((ans1 + ans2) * (k - 1)) % MOD;
        dp[i] = finalAns;
    }

    return dp[n];
}

long long paintSO(int &n, int &k) {
    // Step 1: Create variables
    long long prev2 = k;
    long long prev1 = k + (k * (k - 1));

    // Step 2: Start bottom up loop
    for (int i=3; i<=n; i++) {
        long long currAns = ((prev2 + prev1) * (k - 1)) % MOD;
        // Update variables for the next iteration
        prev2 = prev1;
        prev1 = currAns;
    }

    return prev1;
}

long long countWays(int n, int k){
    
    // Recursion
    /*
    return paintRec(n, k);
    */

    // Memoization
    /*
    vector<int> dp(n + 1, -1);
    return paintMem(n, k, dp);
    */

    // Tabulation
    /*
    return paintTab(n, k);
    */

    // Space Optimization
    return paintSO(n, k);
}


// 5.



int main() {
    int n1 = 3, k1 = 2;
    int n2 = 2, k2 = 4;
    cout << "Paint Fences Recursion n = 3, k = 2: " << paintRec(n1, k1) << endl;
    cout << "Paint Fences Recursion n = 2, k = 4: " << paintRec(n2, k2) << endl;
    
    vector<int> dp1(n1 + 1, -1);
    vector<int> dp2(n2 + 1, -1);
    cout << "\nPaint Fences Memoization n = 3, k = 2: " << paintMem(n1, k1, dp1) << endl;
    cout << "Paint Fences Memoization n = 2, k = 4: " << paintMem(n2, k2, dp2) << endl;

    cout << "\nPaint Fences Tabulation n = 3, k = 2: " << paintTab(n1, k1) << endl;
    cout << "Paint Fences Tabulation n = 2, k = 4: " << paintTab(n2, k2) << endl;

    cout << "\nPaint Fences Space Optimization n = 3, k = 2: " << paintSO(n1, k1) << endl;
    cout << "Paint Fences Space Optimization n = 2, k = 4: " << paintSO(n2, k2) << endl;

    return 0;
}