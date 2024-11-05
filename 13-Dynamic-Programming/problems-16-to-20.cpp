#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

// 16. Perfect Squares
int nsRec(int n) {
    // Base Case
    if (n < 0) return INT_MAX;
    if (n == 0) return 0;

    // Ek Case
    int ans = INT_MAX;

    for (int num=1; num<=sqrt(n); num++) {
        int currAns = nsRec(n - (num * num));
        if (currAns != INT_MAX)
            ans = min(ans, currAns + 1);
    }

    return ans;
}

int nsMem(int n, vector<int>& dp) {
    // Base Case
    if (n < 0) return INT_MAX;
    if (n == 0) return 0;

    // DP Case
    if (dp[n] != -1) return dp[n];

    // Ek Case
    int ans = INT_MAX;

    for (int num=1; num<=sqrt(n); num++) {
        int currAns = nsMem(n - (num * num), dp);
        if (currAns != INT_MAX) ans = min(ans, currAns + 1);
    }

    dp[n] = ans;
    return ans;
}

int nsTab(int &input) {
    // Step 1: Create DP Array
    vector<int> dp(input + 1, INT_MAX);
    // Step 2: Base Case
    dp[0] = 0;
    // Step 3: Bottom Up
    for (int n=1; n<=input; n++) {
        int ans = INT_MAX;
        for (int num=1; num<=sqrt(n); num++) {
            int squaredNum = num * num;
            if (n - squaredNum >= 0) {
                int currAns = dp[n - squaredNum];
                if (currAns != INT_MAX) ans = min(ans, currAns + 1);
            }
        }
        dp[n] = ans;
    }

    return dp[input];
}

int numSquares(int n) {
    // Recursion Solution
    /*
    return nsRec(n);
    */

    // Memoization Solution
    /*
    vector<int> dp(n + 1, -1);
    return nsMem(n, dp);
    */
    
    // Tabulation Solution
    return nsTab(n);
}


// 17. Minimum Cost for Tickets
int mctRec(vector<int>& days, vector<int>& costs, int i) {
    // Base Case
    if (i >= days.size()) return 0;

    // Ek Case
    int passValidity, j;

    // Buy 1 day pass
    int oneDay = costs[0] + mctRec(days, costs, i + 1);

    // Buy 7 day pass
    passValidity = days[i] + 6;
    j = i;
    while (j < days.size() && days[j] <= passValidity) j++;
    int sevenDay = costs[1] + mctRec(days, costs, j);

    // Buy 30 day pass
    passValidity = days[i] + 29;
    j = i;
    while (j < days.size() && days[j] <= passValidity) j++;
    int thirtyDay = costs[2] + mctRec(days, costs, j);

    return min(oneDay, min(sevenDay, thirtyDay));
}

int mctMem(vector<int>& days, vector<int>& costs, int i, vector<int>& dp) {
    // Base Case
    if (i >= days.size()) return 0;

    // DP Case
    if (dp[i] != -1) return dp[i];

    // Ek Case
    int passValidity, j;

    // Buy 1 day pass
    int oneDay = costs[0] + mctMem(days, costs, i + 1, dp);

    // Buy 7 day pass
    passValidity = days[i] + 6;
    j = i;
    while (j < days.size() && days[j] <= passValidity) j++;
    int sevenDay = costs[1] + mctMem(days, costs, j, dp);

    // Buy 30 day pass
    passValidity = days[i] + 29;
    j = i;
    while (j < days.size() && days[j] <= passValidity) j++;
    int thirtyDay = costs[2] + mctMem(days, costs, j, dp);

    dp[i] = min(oneDay, min(sevenDay, thirtyDay));
    return dp[i];
}

int mctTab(vector<int>& days, vector<int>& costs) {
    // Step 1: Create DP Array
    vector<int> dp(days.size() + 30, 0);
    // Step 2: Base Case
    
    // Step 3: Bottom up
    for (int i=days.size()-1; i>=0; i--) {
        
        int passValidity, j;

        // Buy 1 day pass
        int oneDay = costs[0] + dp[i + 1];

        // Buy 7 day pass
        passValidity = days[i] + 6;
        j = i;
        while (j < days.size() && days[j] <= passValidity) j++;
        int sevenDay = costs[1] + dp[j];

        // Buy 30 day pass
        passValidity = days[i] + 29;
        j = i;
        while (j < days.size() && days[j] <= passValidity) j++;
        int thirtyDay = costs[2] + dp[j];

        dp[i] = min(oneDay, min(sevenDay, thirtyDay));
    }
    return dp[0];
}

int mincostTickets(vector<int>& days, vector<int>& costs) {
    // Recursion Solution
    /*
    return mctRec(days, costs, 0);
    */
    
    // Memoization Solution
    /*
    vector<int> dp(days.size(), -1);
    return mctMem(days, costs, 0, dp);
    */
    
    // Tabulation Solution
    return mctTab(days, costs);
}


// 18.


// 19.


// 20.



int main() {

    

    return 0;
}