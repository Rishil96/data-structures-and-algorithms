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


// 27. 


// 28.


// 29.


// 30.



int main() {

    

    return 0;
}