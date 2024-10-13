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


// 2.


// 3.


// 4.


// 5.



int main() {
    

    return 0;
}