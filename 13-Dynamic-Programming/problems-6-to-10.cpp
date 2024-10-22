#include <iostream>
#include <vector>
#include <map>
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


// 9. Minimum Cost Tree from leaf values
int mflRec(vector<int>& arr, map<pair<int, int>, int> &getElementInRange, int start, int end) {
    // Base Case: For invalid range or leaf node we can't get max non-leaf node sum
    if (start >= end) return 0;
    
    // Ek Case: Partition the array, when start, end is a valid range it is not a leaf node scenario
    int ans = INT_MAX;
    
    for (int i=start; i<end; i++) {
        // i is used for partitioning

        // Calculate current node value i.e. product of max element from left and right side of partition index i
        int currNodeVal = getElementInRange[{start, i}] * getElementInRange[{i + 1, end}];

        // Solve for left subarray and right subarray
        int leftAns = mflRec(arr, getElementInRange, start, i);
        int rightAns = mflRec(arr, getElementInRange, i + 1, end);

        // Update answer by adding all non-leaf node values
        ans = min(ans, currNodeVal + leftAns + rightAns);
    }

    return ans;
}

int mflMem(vector<int>& arr, map<pair<int, int>, int> &getElementInRange, int start, int end, vector<vector<int>> &dp) {
    // Base Case
    if (start >= end) return 0;

    // DP Case
    if (dp[start][end] != -1) return dp[start][end];

    // Ek Case
    int ans = INT_MAX;
    
    for (int i=start; i<end; i++) {
        // i is used for partitioning

        // Calculate current node value i.e. product of max element from left and right side of partition index i
        int currNodeVal = getElementInRange[{start, i}] * getElementInRange[{i + 1, end}];

        // Solve for left subarray and right subarray
        int leftAns = mflMem(arr, getElementInRange, start, i, dp);
        int rightAns = mflMem(arr, getElementInRange, i + 1, end, dp);

        // Update answer by adding all non-leaf node values
        ans = min(ans, currNodeVal + leftAns + rightAns);
    }

    dp[start][end] = ans;
    return ans;

}

int mflTab(vector<int>& arr, map<pair<int, int>, int> &getElementInRange) {
    
    int n = arr.size();

    // Step 1: Create DP Array
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    // Step 2: Base Case add is not needed

    // Step 3: Bottom up approach
    for (int start=n-1; start>=0; start--) {
        for (int end=0; end<n; end++) {
            
            if (start >= end) continue;
            int ans = INT_MAX;
            
            for (int i=start; i<end; i++) {

                int currNodeVal = getElementInRange[{start, i}] * getElementInRange[{i + 1, end}];
                // Solve for left subarray and right subarray
                int leftAns = dp[start][i];
                int rightAns = dp[i + 1][end];

                // Update answer by adding all non-leaf node values
                ans = min(ans, currNodeVal + leftAns + rightAns);
            }

            dp[start][end] = ans;
        }
    }

    return dp[0][n-1];
}

int mctFromLeafValues(vector<int>& arr) {
    // Step 1. Calculate the maximum element of every subarray range
    map<pair<int, int>, int> maxElementInRange;

    for (int i=0; i<arr.size(); i++) {
        // Maximum element in range (i, i) is arr[i]
        maxElementInRange[{i, i}] = arr[i];

        for (int j=i+1; j<arr.size(); j++) {
            // Maximum element in range i to j will be the maximum between current element j and the previous range i to j - 1
            maxElementInRange[{i, j}] = max(arr[j], maxElementInRange[{i, j-1}]);
        }
    }

    // Recursion Solution
    /*
    return mflRec(arr, maxElementInRange, 0, arr.size()-1);
    */

    // Memoization Solution
    /*
    vector<vector<int>> dp(arr.size(), vector<int>(arr.size(), -1));
    return mflMem(arr, maxElementInRange, 0, arr.size()-1, dp);
    */

    // Tabulation Solution
    return mflTab(arr, maxElementInRange);
}


// 10. Longest Common Subsequence
int lcsRec(string &text1, string &text2, int i, int j) {
    // Base Case
    if (i >= text1.size() || j >= text2.size()) return 0;

    // Ek Case
    // Both current characters match
    int ans;
    if (text1[i] == text2[j]) {
        ans = lcsRec(text1, text2, i + 1, j + 1) + 1;
    }
    // If current characters don't match, then try moving index of each text once
    else {
        int ans1 = lcsRec(text1, text2, i + 1, j) + 0;
        int ans2 = lcsRec(text1, text2, i, j + 1) + 0;

        ans = max(ans1, ans2);
    }

    return ans;
}

int lcsMem(string &text1, string &text2, int i, int j, vector<vector<int>> &dp) {
    // Base Case
    if (i < 0 || j < 0) return 0;

    // DP Case
    if (dp[i][j] != -1) return dp[i][j];

    // Ek Case
    int ans;
    if (text1[i] == text2[j]) {
        ans = lcsMem(text1, text2, i-1, j-1, dp) + 1;
    }
    else {
        int ans1 = lcsMem(text1, text2, i-1, j, dp) + 0;
        int ans2 = lcsMem(text1, text2, i, j-1, dp) + 0;
        ans = max(ans1, ans2);
    }

    dp[i][j] = ans;

    return ans;
}

int lcsTab(string &text1, string &text2) {
    // Step 1 : Create DP Array
    vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size(), 0));
    // Step 2 : Base Case Add kar (iss case me kuch add nahi karna)
    // Step 3 : Bottom up jaa
    for (int i=0; i<text1.size(); i++) {
        for (int j=0; j<text2.size(); j++) {
            int ans;
            if (text1[i] == text2[j]) {
                if (i - 1 >= 0 && j - 1 >= 0)
                    ans = dp[i-1][j-1] + 1;
                else ans = 1;
            }
            else {
                int ans1 = 0;
                if (i - 1 >= 0)
                    ans1 = dp[i-1][j] + 0;
                int ans2 = 0;
                if (j - 1 >= 0)
                    ans2 = dp[i][j-1] + 0;
                ans = max(ans1, ans2);
            }

            dp[i][j] = ans;
        }
    }

    return dp[text1.size() - 1][text2.size() - 1];
}

int lcsSO(string &text1, string &text2) {
    // Step 1: Create variables
    vector<int> curr(text1.size() + text2.size() + 1, 0);
    vector<int> next(text1.size() + text2.size() + 1, 0);

    // Step 2: Bottom Up
    for (int i=0; i<text1.size(); i++) {
        for (int j=0; j<text2.size(); j++) {
            int ans;
            if (text1[i] == text2[j]) {
                if (i - 1 >= 0 && j - 1 >= 0)
                    ans = curr[j-1] + 1;
                else ans = 1;
            }
            else {
                int ans1 = 0;
                if (i - 1 >= 0)
                    ans1 = curr[j] + 0;
                int ans2 = 0;
                if (j - 1 >= 0)
                    ans2 = next[j-1] + 0;
                ans = max(ans1, ans2);
            }

            next[j] = ans;
        }

        curr = next;
    }

    return curr[text2.size() - 1];
}

int longestCommonSubsequence(string text1, string text2) {
    // Recursion Solution
    /*
    return lcsRec(text1, text2, 0, 0);        
    */

    // Memoization Solution
    /*
    vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, -1));
    return lcsMem(text1, text2, text1.size()-1, text2.size()-1, dp);
    */

    // Tabulation Solution
    /*
    return lcsTab(text1, text2);
    */

    // Space Optimization Solution
    return lcsSO(text1, text2);
}



int main() {

    

    return 0;
}