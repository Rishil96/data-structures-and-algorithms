#include <iostream>
#include <vector>
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


// 12.


// 13.


// 14.


// 15.



int main() {

    

    return 0;
}