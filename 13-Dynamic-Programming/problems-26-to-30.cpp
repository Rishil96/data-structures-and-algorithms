#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 26. Ones and Zeros
int fmfRec(vector<string>& strs, int m, int n, int i, unordered_map<string, pair<int, int>> &freq) {
    // Base Case
    if (i >= strs.size()) return 0;
    if (m <= 0 && n <= 0) return 0;
    // Ek Case
    // Include
    pair<int, int> currFreq = freq[strs[i]];
    int include = 0;
    if (currFreq.first <= m && currFreq.second <= n) {
        include = 1 + fmfRec(strs, m - currFreq.first, n - currFreq.second, i + 1, freq);
    }
    // Exclude
    int exclude = 0 + fmfRec(strs, m, n, i + 1, freq);
    return max(include, exclude);
}

int fmfMem(vector<string>& strs, int m, int n, int i, unordered_map<string, pair<int, int>> &freq,vector<vector<vector<int>>> &dp) {
    // Base Case
    if (i >= strs.size()) return 0;
    if (m <= 0 && n <= 0) return 0;
    // DP Case
    if (dp[m][n][i] != -1) return dp[m][n][i];

    // Ek Case
    // Include
    pair<int, int> currFreq = freq[strs[i]];
    int include = 0;
    if (currFreq.first <= m && currFreq.second <= n) {
        include = 1 + fmfMem(strs, m - currFreq.first, n - currFreq.second, i + 1, freq, dp);
    }
    // Exclude
    int exclude = 0 + fmfMem(strs, m, n, i + 1, freq, dp);
    dp[m][n][i] = max(include, exclude);
    return dp[m][n][i];
}

int fmfTab(vector<string>& strs, int &mVal, int &nVal, unordered_map<string, pair<int, int>> &freq) {
    // Step 1: Create DP Array
    vector<vector<vector<int>>> dp(strs.size() + 1, vector<vector<int>> (mVal + 1, vector<int> (nVal + 1, 0)));
    // Step 2: Base Case
    // Step 3: Bottom up
    for (int m=0; m<=mVal; m++) {
        for (int n=0; n<=nVal; n++) {
            for (int i=strs.size()-1; i>=0; i--) {
                pair<int, int> currFreq = freq[strs[i]];
                int include = 0;
                if (currFreq.first <= m && currFreq.second <= n) {
                    include = 1 + dp[i + 1][m - currFreq.first][n - currFreq.second];
                }
                // Exclude
                int exclude = 0 + dp[i + 1][m][n];
                dp[i][m][n] = max(include, exclude);
            }
        }
    }
    return dp[0][mVal][nVal];
}

int findMaxForm(vector<string>& strs, int m, int n) {
    // Build frequency map
    unordered_map<string, pair<int, int>> freq;
    for (auto s: strs) {
        if (freq.find(s) == freq.end()) {
            int zero = 0;
            int one = 0;
            for (auto num: s) {
                if (num == '0') zero++;
                else one++;
            }
            freq[s] = {zero, one};
        }
    }

    // Recursion Solution
    /*
    return fmfRec(strs, m, n, 0, freq);
    */
    // Memoization Solution
    /*
    vector<vector<vector<int>>> dp(m + 1, vector<vector<int>> (n + 1, vector<int> (strs.size(), -1)));
    return fmfMem(strs, m, n, 0, freq, dp);
    */
    // Tabulation Solution
    return fmfTab(strs, m, n, freq);
}


// 27. Minimum Swaps to make sequences increasing
int msRec(vector<int>& nums1, vector<int>& nums2, int i, int p1, int p2, int swap) {
    // Base Case
    if (i >= nums1.size()) return 0;

    // Ek Case
    int swapped = INT_MAX, notSwapped = INT_MAX;
    /*
    Swap Num: 
    Only swap if both of the below conditions are true
        - current nums1 element i.e. i is greater than previous nums2 element so it fits in nums2 array
        - current nums2 element i.e. i is greater than previous nums1 element so it fits in nums1 array
    */ 
    if (nums1[i] > p2 && nums2[i] > p1) {
        swapped = 1 + msRec(nums1, nums2, i + 1, nums2[i], nums1[i], 1);
    }
    /* 
    Don't swap num if:
        - previous nums1 element is smaller than current nums1 element
        - previous nums2 element is smaller than current nums2 element
    */
    if (p1 < nums1[i] && p2 < nums2[i]) {
        notSwapped = 0 + msRec(nums1, nums2, i + 1, nums1[i], nums2[i], 0);
    }

    return min(swapped, notSwapped);
}

int msMem(vector<int>& nums1, vector<int>& nums2, int i, int prevArr1Num, int prevArr2Num, int swap, vector<vector<int>> &dp) {
    // Base Case
    if (i >= nums1.size()) return 0;

    // DP Case
    if (dp[i][swap] != -1) return dp[i][swap];

    // Ek Case
    int swapped = INT_MAX, notSwapped = INT_MAX;

    // Swap Case
    if (nums1[i] > prevArr2Num && nums2[i] > prevArr1Num) {
        swapped = 1 + msMem(nums1, nums2, i + 1, nums2[i], nums1[i], 1, dp);
    }
    // Not Swap Case
    if (prevArr1Num < nums1[i] && prevArr2Num < nums2[i]) {
        notSwapped = 0 + msMem(nums1, nums2, i + 1, nums1[i], nums2[i], 0, dp);
    }

    dp[i][swap] = min(swapped, notSwapped);
    return dp[i][swap];
} 

int minSwap(vector<int>& nums1, vector<int>& nums2) {
    // Recursion Solution
    /*
    return msRec(nums1, nums2, 0, -1, -1, 0);
    */

    // Memoization Solution
    vector<vector<int>> dp(nums1.size(), vector<int>(2, -1));
    return msMem(nums1, nums2, 0, -1, -1, 0, dp);
}


// 28. Longest Palindromic Substring
int maxLen = 1, startIndex = 0;

bool lpRec(string &s, int start, int end) {
    // Base Case
    if (start >= end) return true;

    // Ek Case
    bool flag = false;
    
    if (s[start] == s[end]) {
        flag = lpRec(s, start + 1, end - 1);
    }

    if (flag) {
        int currLen = end - start + 1;
        if (currLen > maxLen) {
            maxLen = currLen;
            startIndex = start;
        }
    }

    return flag;
}

bool lpMem(string &s, int start, int end, vector<vector<int>> &dp) {
    // Base Case
    if (start >= end) return true;

    // DP Case
    if (dp[start][end] != -1) return dp[start][end];

    // Ek Case
    bool flag = false;
    
    if (s[start] == s[end]) {
        flag = lpMem(s, start + 1, end - 1, dp);
    }

    if (flag) {
        int currLen = end - start + 1;
        if (currLen > maxLen) {
            maxLen = currLen;
            startIndex = start;
        }
    }

    return dp[start][end] = flag;
}

string longestPalindrome(string s) {
    int n = s.size();
    // Recursion Solution
    /*
    for (int start=0; start<n; start++) {
        for (int end=start; end<n; end++) {
            bool ans = lpRec(s, start, end);
        }
    }
    */
    // Memoization Solution
    vector<vector<int>> dp(n, vector<int>(n, -1));
    for (int start=0; start<n; start++) {
        for (int end=start; end<n; end++) {
            bool ans = lpMem(s, start, end, dp);
        }
    }

    return s.substr(startIndex, maxLen);
}


// 29. Minimum ASCII Delete Sum for Two Strings
int mdsRec(string &s1, string &s2, int i, int j) {
    // Base Case
    // Both strings read completely
    if (i >= s1.size() && j >= s2.size()) return 0;
    // s1 read completely
    if (i >= s1.size()) {
        int add = 0;
        for (int x=j; x<s2.size(); x++) add += s2[x];
        return add;
    }
    // s2 read completely
    if (j >= s2.size()) {
        int add = 0;
        for (int x=i; x<s1.size(); x++) add += s1[x];
        return add;
    }
    // Ek Case
    int cost;
    int ascii1 = s1[i];
    int ascii2 = s2[j];
    // If both current characters are equal, don't add ASCII
    if (ascii1 == ascii2) {
        cost = mdsRec(s1, s2, i+1, j+1);
    }
    else {
        // Try deleting 
        int leftAdd = ascii1 + mdsRec(s1, s2, i + 1, j);
        int rightAdd = ascii2 + mdsRec(s1, s2, i, j + 1);
        cost = min(leftAdd, rightAdd);
    }

    return cost;
}

int mdsMem(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) {
    // Base Case
    // Both strings read completely
    if (i >= s1.size() && j >= s2.size()) return 0;
    // s1 read completely
    if (i >= s1.size()) {
        int add = 0;
        for (int x=j; x<s2.size(); x++) add += s2[x];
        return add;
    }
    // s2 read completely
    if (j >= s2.size()) {
        int add = 0;
        for (int x=i; x<s1.size(); x++) add += s1[x];
        return add;
    }

    // DP Case
    if (dp[i][j] != -1) return dp[i][j]; 

    // Ek Case
    int cost;
    int ascii1 = s1[i];
    int ascii2 = s2[j];
    // If both current characters are equal, don't add ASCII
    if (ascii1 == ascii2) {
        cost = mdsMem(s1, s2, i+1, j+1, dp);
    }
    else {
        // Try deleting 
        int leftAdd = ascii1 + mdsMem(s1, s2, i + 1, j, dp);
        int rightAdd = ascii2 + mdsMem(s1, s2, i, j + 1, dp);
        cost = min(leftAdd, rightAdd);
    }

    dp[i][j] = cost;
    return dp[i][j];
} 

int mdsTab(string &s1, string &s2) {
    // Step 1: Create DP Array
    vector<vector<int>> dp(s1.size() + 2, vector<int>(s2.size() + 2, 0));
    // Step 2: Base case handle
    // Remaining to do, the answer returned is not correct due to base case not handled properly
    // Step 3: Bottom up
    for (int i=s1.size()-1; i>=0; i--) {
        for (int j=s2.size()-1; j>=0; j--) {
            // Ek Case
            int cost;
            int ascii1 = s1[i];
            int ascii2 = s2[j];
            // If both current characters are equal, don't add ASCII
            if (ascii1 == ascii2) {
                cost = dp[i+1][j+1];
            }
            else {
                // Try deleting 
                int leftAdd = ascii1 + dp[i + 1][j];
                int rightAdd = ascii2 + dp[i][j + 1];
                cost = min(leftAdd, rightAdd);
            }

            dp[i][j] = cost;
        }
    }

    for (int i=0; i<s1.size(); ++i) {
        for (int j=0; j<s2.size(); ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return dp[0][0];
}

int minimumDeleteSum(string s1, string s2) {
    // Recursion Solution
    /*
    return mdsRec(s1, s2, 0, 0);
    */
    // Memoization Solution
    /*
    vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), -1));
    return mdsMem(s1, s2, 0, 0, dp);
    */
    // Tabulation Solution
    return mdsTab(s1, s2);
}


// 30. Reducing Dishes
int msRec(vector<int>& satisfaction, int i, int &time) {
    // Base Case
    if (i >= satisfaction.size()) return 0;
    // Ek Case
    // Cook current dish
    int cook = satisfaction[i] * time;
    time++;
    cook += msRec(satisfaction, i + 1, time);
    time--;
    // Don't cook current dish
    int dontCook = msRec(satisfaction, i + 1, time);

    return max(cook, dontCook); 
}

int msMem(vector<int>& satisfaction, int i, int &time, vector<vector<int>> &dp) {
    // Base Case
    if (i >= satisfaction.size()) return 0;
    // DP Case
    if (dp[i][time] != -1) return dp[i][time];
    // Ek Case
    // Cook current dish
    int cook = satisfaction[i] * time;
    time++;
    cook += msMem(satisfaction, i + 1, time, dp);
    time--;
    // Don't cook current dish
    int dontCook = msMem(satisfaction, i + 1, time, dp);

    dp[i][time] = max(cook, dontCook);
    return dp[i][time]; 
}

int msTab(vector<int>& sat) {
    // Step 1: Create DP Array
    vector<vector<int>> dp(sat.size() + 1, vector<int>(sat.size() + 2, 0));
    // Step 2: Base Case
    // Step 3: Bottom up approach
    for (int i=sat.size()-1; i>=0; i--) {
        for (int time=sat.size(); time>=1; time--) {
            int cook = sat[i] * time;
            cook += dp[i + 1][time + 1];

            // Don't cook current dish
            int dontCook = dp[i + 1][time];
            dp[i][time] = max(cook, dontCook);
        }
    }
    return dp[0][1]; 
}

int maxSatisfaction(vector<int>& satisfaction) {
    // Sort the dishes as per most disliked to most liked
    sort(satisfaction.begin(), satisfaction.end());
    int time = 1;
    // Recursion Solution
    /*
    return msRec(satisfaction, 0, time);
    */
    // Memoization Solution
    /*
    vector<vector<int>> dp(satisfaction.size(), vector<int>(satisfaction.size() + 1, -1));
    return msMem(satisfaction, 0, time, dp);
    */
    // Tabulation Soluation
    return msTab(satisfaction);
}



int main() {

    

    return 0;
}