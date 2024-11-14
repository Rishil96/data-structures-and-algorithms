#include <iostream>
#include <vector>
#include <unordered_map>
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


// 28.


// 29.


// 30.



int main() {

    

    return 0;
}