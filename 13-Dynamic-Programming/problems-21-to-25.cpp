#include <iostream>
#include <vector>
using namespace std;

// 21. Buy and Sell Stocks 5
int mpRec(vector<int>& prices, int i, int isHolding, int &fee) {
    // Base Case
    if (i >= prices.size()) return 0;
    // Ek Case
    int buyResult = 0, sellResult = 0;
    // Buy Stock
    if (isHolding == 0) {
        int buy = mpRec(prices, i + 1, 1, fee) - prices[i] - fee;
        int skip = mpRec(prices, i + 1, isHolding, fee);
        buyResult = max(buy, skip);
    }
    // Sell Stock
    else {
        int sell = mpRec(prices, i + 1, 0, fee) + prices[i];
        int skip = mpRec(prices, i + 1, isHolding, fee);
        sellResult = max(sell, skip);
    }

    return max(buyResult, sellResult);
}

int mpMem(vector<int>& prices, int i, int isHolding, int &fee, vector<vector<int>> &dp) {
    // Base Case
    if (i >= prices.size()) return 0;
    // DP Case
    if (dp[i][isHolding] != -1) return dp[i][isHolding];
    // Ek Case
    int buyResult = 0, sellResult = 0;
    // Buy Stock
    if (isHolding == 0) {
        int buy = mpMem(prices, i + 1, 1, fee, dp) - prices[i] - fee;
        int skip = mpMem(prices, i + 1, isHolding, fee, dp);
        buyResult = max(buy, skip);
    }
    // Sell Stock
    else {
        int sell = mpMem(prices, i + 1, 0, fee, dp) + prices[i];
        int skip = mpMem(prices, i + 1, isHolding, fee, dp);
        sellResult = max(sell, skip);
    }

    dp[i][isHolding] = max(buyResult, sellResult);
    return dp[i][isHolding];
}

int mpTab(vector<int>& prices, int &fee) {
    // Step 1: Create DP Array
    vector<vector<int>> dp(prices.size() + 1, vector<int>(2, 0));
    // Step 2: Base Case
    // Step 3: Bottom Up
    for (int i=prices.size()-1; i>=0; i--) {
        for (int isHolding=0; isHolding<=1; isHolding++) {

            int buyResult = 0, sellResult = 0;
            // Buy Stock
            if (isHolding == 0) {
                int buy = dp[i + 1][1] - prices[i] - fee;
                int skip = dp[i + 1][isHolding];
                buyResult = max(buy, skip);
            }
            // Sell Stock
            else {
                int sell = dp[i + 1][0] + prices[i];
                int skip = dp[i + 1][isHolding];
                sellResult = max(sell, skip);
            }

            dp[i][isHolding] = max(buyResult, sellResult);
        }
    }
    return dp[0][0];
}

int mpSO(vector<int>& prices, int &fee) {
    // Step 1: Create variables
    vector<int> nextRow(2, 0);
    vector<int> currRow(2, 0);

    // Step 2: Base Case
    // Step 3: Bottom Up
    for (int i=prices.size()-1; i>=0; i--) {
        for (int isHolding=0; isHolding<2; isHolding++) {
            int buyResult = 0, sellResult = 0;
            // Buy Stock
            if (isHolding == 0) {
                int buy = nextRow[1] - prices[i] - fee;
                int skip = nextRow[isHolding];
                buyResult = max(buy, skip);
            }
            // Sell Stock
            else {
                int sell = nextRow[0] + prices[i];
                int skip = nextRow[isHolding];
                sellResult = max(sell, skip);
            }

            currRow[isHolding] = max(buyResult, sellResult);
        }
        // Update kar be variables ko
        nextRow = currRow;
    }
    return currRow[0];
}

int maxProfit(vector<int>& prices, int fee) {
    // Recursion Solution
    /*
    return mpRec(prices, 0, 0, fee);
    */
    // Memoization Solution
    /*
    vector<vector<int>> dp(prices.size(), vector<int>(2, -1));
    return mpMem(prices, 0, 0, fee, dp);
    */
    // Tabulation Solution
    /*
    return mpTab(prices, fee);
    */
    // Space Optimization Solution
    return mpSO(prices, fee);
}


// 22.


// 23.


// 24.


// 25.



int main() {

    

    return 0;
}