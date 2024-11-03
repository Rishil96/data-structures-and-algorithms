#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 11. Longest Palindromic Subsequence
int lpsRec(string &s, int &l, int &r) {
    // Base Case
    if (l > r) return 0;
    if (l == r) return 1;
    
    // Ek Case
    int ans;
    // If both left and right characters are equal, use it in subsequence by adding 2
    if (s[l] == s[r]) {
        l++; r--;
        ans = lpsRec(s, l, r) + 2;
        l--; r++;
    }
    // Else try skipping left character once and right character once 
    else {
        l++;
        int skipLeft = lpsRec(s, l, r);
        l--;
        r--;
        int skipRight = lpsRec(s, l, r);
        r++;

        ans = max(skipLeft, skipRight);
    }

    return ans;
}

int lpsMem(string &s, int &l, int &r, vector<vector<int>> &dp) {
    // Base Case
    if (l > r) return 0;
    if (l == r) return 1;

    // DP Case
    if (dp[l][r] != -1) return dp[l][r];

    // Ek Case
    int ans;
    if (s[l] == s[r]) {
        l++; r--;
        ans = lpsMem(s, l, r, dp) + 2;
        l--; r++;
    }
    else {
        l++;
        int skipLeft = lpsMem(s, l, r, dp);
        l--;
        r--;
        int skipRight = lpsMem(s, l, r, dp);
        r++;
        ans = max(skipLeft, skipRight);
    }

    dp[l][r] = ans;
    return ans;
}

int lpsTab(string &s) {
    // Step 1: Create dp array
    vector<vector<int>> dp(s.size() + 1, vector<int>(s.size() + 1, 0));

    // Step 2: Base Case
    for (int i=0; i<s.size(); i++) {
        dp[i][i] = 1;
    }
    // Step 3: Bottom up
    for (int l=s.size() - 1; l>=0; l--) {
        for (int r=0; r<s.size(); r++) {
            // Base Case for invalid range
            if (l >= r) continue;

            // Process
            int ans;
            if (s[l] == s[r]) {
                if (l + 1 >= s.size() || r - 1 < 0) {
                    ans = 2;
                }
                else {
                    ans = dp[l+1][r-1] + 2;
                }
            }
            else {
                int skipLeft = 0, skipRight = 0;
                if (l + 1 < s.size()) {
                    skipLeft = dp[l + 1][r];
                }
                if (r - 1 >= 0) {
                    skipRight = dp[l][r - 1];
                }
                ans = max(skipLeft, skipRight);
            }

            dp[l][r] = ans;
        }
    }

    return dp[0][s.size() - 1];
}

int longestPalindromeSubseq(string s) {
    
    int l = 0;
    int r = s.size() - 1;

    // Recursion Solution
    /*
    return lpsRec(s, l, r);
    */

    // Memoization Solution
    /*
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), -1));
    return lpsMem(s, l, r, dp);
    */

    // Tabulation Solution
    return lpsTab(s);
}


// 12. Edit Distance
int mdRec(string &word1, string &word2, int i, int j) {
    // Base Case
    if (i >= word1.size() && j >= word2.size()) return 0;
    if (i >= word1.size()) return word2.size() - j;
    if (j >= word2.size()) return word1.size() - i;

    // Ek Case

    // Move ahead if current 2 characters on indexes match
    int ans;
    if (word1[i] == word2[j]) {
        ans = mdRec(word1, word2, i+1, j+1);
    }
    // Else perform insert, replace, delete operations
    else {
        // Insert character in word2
        int ans1 = mdRec(word1, word2, i, j + 1) + 1;
        // Delete character in word1
        int ans2 = mdRec(word1, word2, i + 1, j) + 1;
        // Replace character in word2
        int ans3 = mdRec(word1, word2, i + 1, j + 1) + 1;

        ans = min(ans1, min(ans2, ans3));
    }

    return ans;
}

int mdMem(string &word1, string &word2, int i, int j, vector<vector<int>> &dp) {
    // Base Case
    if (i >= word1.size() && j >= word2.size()) return 0;
    if (i >= word1.size()) return word2.size() - j;
    if (j >= word2.size()) return word1.size() - i;

    // DP Case
    if (dp[i][j] != -1) return dp[i][j];

    // Ek Case

    // Move ahead if current 2 characters on indexes match
    int ans;
    if (word1[i] == word2[j]) {
        ans = mdMem(word1, word2, i+1, j+1, dp);
    }
    // Else perform insert, replace, delete operations
    else {
        // Insert character in word2
        int ans1 = mdMem(word1, word2, i, j + 1, dp) + 1;
        // Delete character in word1
        int ans2 = mdMem(word1, word2, i + 1, j, dp) + 1;
        // Replace character in word2
        int ans3 = mdMem(word1, word2, i + 1, j + 1, dp) + 1;

        ans = min(ans1, min(ans2, ans3));
    }

    return dp[i][j] = ans;
}

int mdTab(string &word1, string &word2) {
    // Step 1: Create DP Array
    vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
    // Step 2: Base Case
    for (int i=0; i<dp.size(); i++) {
        for (int j=0; j<dp[i].size(); j++) {
            if (i >= word1.size()) dp[i][j] = word2.size() - j;
            if (j >= word2.size()) dp[i][j] = word1.size() - i;
        }
    }

    // Step 3: Bottom Up
    for (int i=word1.size()-1; i>=0; i--) {
        for (int j=word2.size()-1; j>=0; j--) {
            int ans;
            if (word1[i] == word2[j]) {
                ans = dp[i+1][j+1];
            }
            // Else perform insert, replace, delete operations
            else {
                // Insert character in word2
                int ans1 = dp[i][j + 1] + 1;
                // Delete character in word1
                int ans2 = dp[i + 1][j] + 1;
                // Replace character in word2
                int ans3 = dp[i + 1][j + 1] + 1;

                ans = min(ans1, min(ans2, ans3));
            }

            dp[i][j] = ans;
        }
    }

    return dp[0][0];
}

int minDistance(string word1, string word2) {
    // Recursion Solution
    /*
    return mdRec(word1, word2, 0, 0);
    */

    // Memoization Solution
    /*
    vector<vector<int>> dp(word1.size(), vector<int>(word2.size(), -1));
    return mdMem(word1, word2, 0, 0, dp);
    */

    // Tabulation Solution
    return mdTab(word1, word2);
}


// 13. Longest Increasing Subsequence
int lisRec(vector<int>& nums, int currIndex, int prevIndex) {
    /*
    prevIndex: used to keep track of the last used index in the LIS
    currIndex: used to check if current element at currIndex can be used in ongoing LIS
    */
    // Base Case
    if (currIndex >= nums.size()) return 0;
    // Ek Case
    int include = 0;
    
    // Include case
    if (prevIndex == -1 || nums[currIndex] > nums[prevIndex]) {
        include = 1 + lisRec(nums, currIndex + 1, currIndex);
    }
    int exclude = 0 + lisRec(nums, currIndex + 1, prevIndex);

    return max(include, exclude);
}

int lisMem(vector<int>& nums, int currIndex, int prevIndex, vector<vector<int>> &dp) {
    // Base Case
    if (currIndex >= nums.size()) return 0;

    // DP Case
    if (dp[currIndex][prevIndex + 1] != -1) return dp[currIndex][prevIndex + 1];

    // Ek Case
    int include = 0;
    if (prevIndex == -1 || nums[currIndex] > nums[prevIndex]) {
        include = 1 + lisMem(nums, currIndex + 1, currIndex, dp);
    }

    int exclude = 0 + lisMem(nums, currIndex + 1, prevIndex, dp);

    dp[currIndex][prevIndex + 1] = max(include, exclude);
    return dp[currIndex][prevIndex + 1];
}

int lisTab(vector<int>& nums) {
    int n = nums.size();
    // Step 1: Create DP Array
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    // Step 2: Base Case (nothing to add)
    // Step 3: Bottom Up Approach
    for (int curr=n-1; curr>=0; curr--) {
        for (int prev=curr-1; prev>=-1; prev--) {
            int include = 0;
            if (prev == -1 || nums[curr] > nums[prev]) {
                include = 1 + dp[curr+1][curr+1];
            }

            int exclude = dp[curr+1][prev+1];

            dp[curr][prev+1] = max(include, exclude);
        }
    }

    return dp[0][0];
}

int lisSO(vector<int>& nums) {
    int n = nums.size();
    // Step 1: Create variables
    vector<int> currRow(n + 1, 0);
    vector<int> nextRow(n + 1, 0);

    // Step 2: Bottom up
    for (int curr=n-1; curr>=0; curr--) {
        for (int prev=curr-1; prev>=-1; prev--) {
            int include = 0;

            if (prev == -1 || nums[curr] > nums[prev]) {
                include = 1 + nextRow[curr+1];
            }
            int exclude = 0 + nextRow[prev+1];
            currRow[prev+1] = max(include, exclude);
        }

        // Shift to update variables for next iteration
        nextRow = currRow;
    }

    return nextRow[0];
}

int lisSOBS(vector<int>& nums) {
    // Step 1: Create answer array
    vector<int> ans;
    ans.push_back(nums[0]);

    // Step 2: Loop through the array
    for (int i=1; i<nums.size(); i++) {
        int currNum = nums[i];
        // If current number is the largest as per answer array then add it in answer
        if (currNum > ans.back()) {
            ans.push_back(currNum);
        }
        // Else there exist a number that is just larger than current number
        // Find the number that is just larger than current number and replace that number with current number
        else {
            int justLargerIndex = lower_bound(ans.begin(), ans.end(), currNum) - ans.begin();
            ans[justLargerIndex] = currNum;
        }
    }

    return ans.size();
}

int lengthOfLIS(vector<int>& nums) {
    // Recursion Solution
    /*
    return lisRec(nums, 0, -1);
    */
    
    // Memoization Solution
    /*
    vector<vector<int>> dp(nums.size() + 1, vector<int>(nums.size() + 1, -1));
    return lisMem(nums, 0, -1, dp);
    */
    
    // Tabulation Solution
    return lisTab(nums);
}


// 14. Russian Doll Envelope
static bool cmp(vector<int> a, vector<int> b) {
    if (a[0] == b[0]) return a[1] > b[1];
    else return a[0] < b[0];
}

int meRec(vector<vector<int>>& env, int curr, int prev) {
    // Base Case
    if (curr >= env.size()) return 0;

    // Ek Case
    int include = 0;
    if (prev == -1 || (env[curr][0] > env[prev][0] && env[curr][1] > env[prev][1])) {
        include = 1 + meRec(env, curr + 1, curr);
    }
    int exclude = 0 + meRec(env, curr + 1, prev);

    return max(include, exclude);
}

int meMem(vector<vector<int>>& env, int curr, int prev, vector<vector<int>> &dp) {
    // Base Case
    if (curr >= env.size()) return 0;

    // DP Case
    if (dp[curr][prev + 1] != -1) return dp[curr][prev + 1];

    // Ek Case
    int include = 0;
    if (prev == -1 || (env[curr][0] > env[prev][0] && env[curr][1] > env[prev][1])) {
        include = 1 + meMem(env, curr + 1, curr, dp);
    }
    int exclude = 0 + meMem(env, curr + 1, prev, dp);

    return dp[curr][prev + 1] = max(include, exclude);
}

int meTab(vector<vector<int>>& env) {
    // Step 1: Create DP array
    vector<vector<int>> dp(env.size()+2, vector<int>(env.size()+2, 0));

    // Step 2: Handle base case in DP array
    
    // Step 3: Bottom Up
    for (int curr=env.size()-1; curr>=0; curr--) {
        for (int prev=curr-1; prev>=-1; prev--) {
            int include = 0;
            if (prev == -1 || (env[curr][0] > env[prev][0] && env[curr][1] > env[prev][1])) {
                include = 1 + dp[curr + 1][curr + 1];
            }
            int exclude = 0 + dp[curr + 1][prev + 1];
            // Update DP Array
            dp[curr][prev + 1] = max(include, exclude);
        }
    }
    
    return dp[0][0];
}

int meSO(vector<vector<int>>& env) {
    // Step 1: Create variables
    vector<int> currRow(env.size() + 1, 0);
    vector<int> nextRow(env.size() + 1, 0);

    // Step 2: Handle base case in DP array
    
    // Step 3: Bottom Up
    for (int curr=env.size()-1; curr>=0; curr--) {
        for (int prev=curr-1; prev>=-1; prev--) {
            int include = 0;
            if (prev == -1 || (env[curr][0] > env[prev][0] && env[curr][1] > env[prev][1])) {
                include = 1 + nextRow[curr + 1];
            }
            int exclude = 0 + nextRow[prev + 1];
            // Update DP Array
            currRow[prev + 1] = max(include, exclude);
        }

        // Update variables for next iteration
        nextRow = currRow;
    }
    
    return nextRow[0];
}

int meSOBS(vector<vector<int>>& env) {
    // Super optimized method using Binary Search
    
    // Step 1: Create answer array that will store the longest increasing subsequence
    vector<int> ans;
    ans.push_back(env[0][1]);

    // Step 2: Loop through rest of the array after adding first element in ans
    for (int i=1; i<env.size(); i++) { 
        // If current element is greater than last element of ans, push it in answer
        if (env[i][1] > ans.back()) {
            ans.push_back(env[i][1]);
        }
        // Else find the element just greater than current element in ans and replace it
        else {
            int index = lower_bound(ans.begin(), ans.end(), env[i][1]) - ans.begin();
            ans[index] = env[i][1];
        }
    }

    return ans.size();
}

int maxEnvelopes(vector<vector<int>>& envelopes) {
    sort(envelopes.begin(), envelopes.end(), cmp);

    // for (int i=0; i<envelopes.size(); i++) {
    //     cout << envelopes[i][0] << ", " << envelopes[i][1] << endl;
    // }

    // Recursion Solution
    /*
    return meRec(envelopes, 0, -1);
    */

    // Memoization Solution
    vector<vector<int>> dp(envelopes.size() + 1, vector<int>(envelopes.size(), -1));
    return meMem(envelopes, 0, -1, dp);
}

// 15.



int main() {

    

    return 0;
}