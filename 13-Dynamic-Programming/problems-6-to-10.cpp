#include <iostream>
#include <vector>
using namespace std;


// 6. Partition Equals Subset Sum
bool partRec(vector<int>& nums, int &i, int &target) {
    // Base Case
    if (target == 0) return true;
    if (target < 0 || i >= nums.size()) return false;

    // Ek Case
    // Include 
    i++;
    target -= nums[i];
    bool include = partRec(nums, i, target);
    i--;
    target += nums[i];

    // Exclude
    i++;
    bool exclude = partRec(nums, i, target); 
    i--;

    return include || exclude;
}

bool partMem(vector<int>& nums, int &i, int &target, vector<vector<int>> &dp) {
    // Base Case
    if (target < 0 || i < 0) return false;
    if (target == 0) return true;

    // DP Case
    if (dp[i][target] != -1) return dp[i][target];

    // Ek Case
    target -= nums[i];
    i--;
    bool include = partMem(nums, i, target, dp);
    i++;
    target += nums[i];

    i--;
    bool exclude = partMem(nums, i, target, dp);
    i++;

    dp[i][target] = include || exclude;
    return dp[i][target];
}

bool partTab(vector<int>& nums, int &target) {
    // Step 1: Create dp array
    vector<vector<bool>> dp(nums.size(), vector<bool>(target + 1, 0));
    // display(dp);

    // Step 2: Update base case (for target = 0 for every row, result is true)
    for (int i=0; i<dp.size(); i++) {
        dp[i][0] = 1;
    }

    // Step 3: Bottom up approach
    for (int index=1; index<nums.size(); index++) {
        for (int t=1; t<=target; t++) {

            // Include Case
            bool include = 0;
            if (t - nums[index] >= 0) {
                include = dp[index - 1][t - nums[index]];
            }

            // Exclude Case
            bool exclude = dp[index - 1][t];
            
            // Update current answer
            dp[index][t] = include || exclude;
        }
    }
    return dp[nums.size()-1][target];
}

bool partSO(vector<int>& nums, int &target) {
    // Step 1: Create variables
    vector<int> prev(target + 1, 0);        // Initially acts as answer of 0th row from tabulation soln
    vector<int> curr(target + 1, 0);        // Initially its the starting point to build ans from 1st index

    // Step 2: Update base case
    prev[0] = 1;
    curr[0] = 1;

    // Step 3: Bottom up
    for (int i=1; i<nums.size(); i++) {
        for (int t=0; t<=target; t++) {
            // Include Case
            bool include = 0;
            if (t - nums[i] >= 0) {
                include = prev[t - nums[i]];
            }
            // Exclude Case
            bool exclude = prev[t];
            
            // Update current answer
            curr[t] = include || exclude;

        }
        // Update previous array
        prev = curr;
    }

    return prev[target];
}

bool canPartition(vector<int>& nums) {
    int totalSum = 0;
    for (auto num: nums) totalSum += num;

    if (totalSum & 1) return false;
    int target = totalSum / 2;
    int index = nums.size() - 1;

    // Recursion Solution
    /*
    return partRec(nums, index, target);
    */

    // Memoization Solution
    /*
    vector<vector<int>> dp(nums.size(), vector<int>(target + 1, -1));
    return partMem(nums, index, target, dp);
    */

    // Tabulation Solution
    /*
    return partTab(nums, target);
    */

    // Space Optimization Solution
    return partSO(nums, target);
}


// 7. Number of dice rolls to target sum
int MOD = 1000000007;

int nrttRec(int n, int &k, int target) {
    // Base Case
    if (n == 0 && target == 0) return 1;
    if (n <= 0 || target < 0) return 0;

    // Ek Case
    int ways = 0;
    for (int face=1; face<=k; face++) {
        int currAns = nrttRec(n - 1, k, target - face);
        ways += currAns;
    }

    return ways;
}

int nrttMem(int n, int &k, int target, vector<vector<int>> &dp) {
    // Base Case
    if (n == 0 && target == 0) return 1;
    if (n <= 0 || target < 0) return 0;

    // DP Case
    if (dp[n][target] != -1) return dp[n][target];

    // Ek Case
    int ways = 0;
    for (int face=1; face <=k; face++) {
        int currAns = nrttMem(n - 1, k, target - face, dp) % MOD;
        ways = (ways % MOD) + (currAns % MOD);
        ways = ways % MOD;
    }
    return dp[n][target] = ways;
}

int nrttTab(int &n, int &k, int &target) {
    // Step 1: Create DP Array
    vector<vector<int>> dp(n+1, vector<int>(target+1, 0));

    // Step 2: Add base case in dp array
    dp[0][0] = 1;
    
    // Step 3: Bottom up approach
    for (int dice=1; dice<=n; dice++) {
        for (int t=1; t<=target; t++) {
            int ways = 0;
            for (int face=1; face<=k; face++) {
                int currAns = 0;
                if (t - face >= 0)
                    currAns = dp[dice - 1][t - face] % MOD;
                ways = (ways % MOD) + (currAns % MOD);
                ways = ways % MOD;
            }
            // Galti yahi hua: Har dice, target combination ke liye answers nikalne ke baad dp array update karna hai
            dp[dice][t] = ways;
        }
    }

    return dp[n][target];
}

int numRollsToTarget(int n, int k, int target) {
    // Recursion Solution
    /*
    return nrttRec(n, k, target);
    */
    
    // Memoization Solution
    /*
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
    return nrttMem(n, k, target, dp);
    */

    // Tabulation Solution
    return nrttTab(n, k, target);
}


// 8. Guess number higher or lower
int gmaRec(int low, int high) {
    // Base Case
    if (low >= high) return 0;

    // Ek Case
    int ans = INT_MAX;

    // Loop through 1 and n to consider every number as a guess
    for (int guess=low; guess<=high; guess++) {
        // Suppose current guess is wrong, pay the penalty (guess amount) and look for correct guess in lower and higher range
        int leftMeAnswer = gmaRec(low, guess - 1) + guess;
        int rightMeAnswer = gmaRec(guess + 1, high) + guess;
        // To make sure we have enough money to win the game, always take the larger amount paid as penalty
        int currAns = max(leftMeAnswer, rightMeAnswer);

        // Update answer to the minimum largest amount we have to pay to win the game
        ans = min(ans, currAns);
    } 

    return ans;
}

int gmaMem(int low, int high, vector<vector<int>>& dp) {
    // Base Case
    if (low >= high) return 0;

    // DP Case
    if (dp[low][high] != -1) return dp[low][high];

    // EK Case
    int ans = INT_MAX;

    for (int guess=low; guess<=high; guess++) {
        int leftAns = gmaMem(low, guess - 1, dp) + guess;
        int rightAns = gmaMem(guess + 1, high, dp) + guess;

        int currAns = max(leftAns, rightAns);
        ans = min(ans, currAns);
    }

    dp[low][high] = ans;
    return ans;
}

int gmaTab(int &n) {
    // Step 1: Create DP Array
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    // Step 2: Base Case add kar
    // Step 3: Bottom Up 
    for (int low=n; low>=1; low--) {
        for (int high=low + 1; high<=n; high++) {
            int ans = INT_MAX;

            for (int guess=low; guess<=high; guess++) {
                int leftAns = dp[low][guess - 1] + guess;
                int rightAns = dp[guess + 1][high] + guess;

                int currAns = max(leftAns, rightAns);
                ans = min(ans, currAns);
            }

            dp[low][high] = ans;
        }
    }

    return dp[1][n];
}

int getMoneyAmount(int n) {
    // Recursion Solution
    /*
    return gmaRec(1, n);
    */

    // Memoization Solution
    /*
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    return gmaMem(1, n, dp);
    */

    // Tabulation Solution
    return gmaTab(n);
}


// 9.


// 10.



int main() {

    

    return 0;
}