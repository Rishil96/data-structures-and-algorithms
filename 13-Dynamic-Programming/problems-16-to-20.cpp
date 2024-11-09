#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>
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


// 18. Buy and Sell Stocks 2
int mpRec(vector<int>& prices, int i, bool isHolding) {
    // Base Case
    if (i >= prices.size()) return 0;

    // Ek Case
    // Buy stock
    int buyResult = 0, sellResult = 0;
    if (!isHolding) {
        int buy = mpRec(prices, i + 1, true) - prices[i];
        int skip = mpRec(prices, i + 1, isHolding);
        buyResult = max(buy, skip);
    }
    // Sell Stock
    else {
        int sell = mpRec(prices, i + 1, false) + prices[i];
        int skip = mpRec(prices, i + 1, isHolding);
        sellResult = max(sell, skip);
    }

    return max(buyResult, sellResult); 
}

int mpMem(vector<int>& prices, int i, bool isHolding, vector<vector<int>>& dp) {
    // Base Case
    if (i >= prices.size()) return 0;

    // DP Case
    if (dp[i][isHolding] != -1) return dp[i][isHolding];

    // Ek Case
    int buyResult = 0, sellResult = 0;
    if (!isHolding) {
        int buy = mpMem(prices, i + 1, true, dp) - prices[i];
        int skip = mpMem(prices, i + 1, isHolding, dp);
        buyResult = max(buy, skip);
    }
    // Sell Stock
    else {
        int sell = mpMem(prices, i + 1, false, dp) + prices[i];
        int skip = mpMem(prices, i + 1, isHolding, dp);
        sellResult = max(sell, skip);
    }

    dp[i][isHolding] = max(buyResult, sellResult);
    return dp[i][isHolding];
}

int mpTab(vector<int>& prices) {
    // Step 1: DP Array
    vector<vector<int>> dp(prices.size() + 1, vector<int>(2, 0));
    // Step 2: Base Case addition

    // Step 3: Bottom Up
    for (int i=prices.size()-1; i>=0; i--) {
        for (int isHolding=0; isHolding<=1; isHolding++) {
            int buyResult = 0, sellResult = 0;
            if (!isHolding) {
                int buy = dp[i + 1][true] - prices[i];
                int skip = dp[i + 1][isHolding];
                buyResult = max(buy, skip);
            }
            // Sell Stock
            else {
                int sell = dp[i + 1][false] + prices[i];
                int skip = dp[i + 1][isHolding];
                sellResult = max(sell, skip);
            }

            dp[i][isHolding] = max(buyResult, sellResult);
        }
    }

    return dp[0][0];
}

int mpSO(vector<int>& prices) {
    // Step 1: DP Array
    vector<int> currRow(2, 0);
    vector<int> nextRow(2, 0);
    // Step 2: Base Case addition

    // Step 3: Bottom Up
    for (int i=prices.size()-1; i>=0; i--) {
        for (int isHolding=0; isHolding<=1; isHolding++) {
            int buyResult = 0, sellResult = 0;
            if (!isHolding) {
                int buy = nextRow[true] - prices[i];
                int skip = nextRow[isHolding];
                buyResult = max(buy, skip);
            }
            // Sell Stock
            else {
                int sell = nextRow[false] + prices[i];
                int skip = nextRow[isHolding];
                sellResult = max(sell, skip);
            }

            currRow[isHolding] = max(buyResult, sellResult);
        }

        nextRow = currRow;
    }

    return currRow[0];
}

int maxProfit(vector<int>& prices) {
    // Recursion Solution
    /*
    return mpRec(prices, 0, false);
    */
    // Memoization Solution
    /*
    vector<vector<int>> dp(prices.size(), vector<int>(2, -1));
    return mpMem(prices, 0, false, dp);
    */
    // Tabulation Solution
    return mpTab(prices);
}


// 19. Buy and Sell Stocks 3
int mp2Rec(vector<int>& prices, int i, int isHolding, int limit) {
    // Base Case
    if (i >= prices.size() || limit == 0) return 0;

    // Ek Case
    int buyResult = 0, sellResult = 0;
    // Buy Stock
    if (isHolding == 0) {
        // Buy Stock
        int buy = mp2Rec(prices, i + 1, 1, limit) - prices[i];
        // Skip buying
        int skip = mp2Rec(prices, i + 1, isHolding, limit);

        buyResult = max(buy, skip);
    }
    // Sell Stock
    else {
        // Sell Stock
        int sell = mp2Rec(prices, i + 1, 0, limit - 1) + prices[i];
        // Skip selling
        int skip = mp2Rec(prices, i + 1, isHolding, limit);

        sellResult = max(sell, skip);
    }

    return max(buyResult, sellResult);
}

int mp2Mem(vector<int>& prices, int i, int isHolding, int limit, vector<vector<vector<int>>> &dp) {
    // Base Case
    if (i >= prices.size() || limit == 0) return 0;

    // DP Case
    if (dp[i][isHolding][limit] != -1) return dp[i][isHolding][limit];

    // Ek Case
    int buyResult = 0, sellResult = 0;
    // Buy Stock
    if (isHolding == 0) {
        // Buy Stock
        int buy = mp2Mem(prices, i + 1, 1, limit, dp) - prices[i];
        // Skip buying
        int skip = mp2Mem(prices, i + 1, isHolding, limit, dp);

        buyResult = max(buy, skip);
    }
    // Sell Stock
    else {
        // Sell Stock
        int sell = mp2Mem(prices, i + 1, 0, limit - 1, dp) + prices[i];
        // Skip selling
        int skip = mp2Mem(prices, i + 1, isHolding, limit, dp);

        sellResult = max(sell, skip);
    }

    dp[i][isHolding][limit] = max(buyResult, sellResult);
    return dp[i][isHolding][limit];
}

int mp2Tab(vector<int>& prices) {
    int transactionLimit = 2;      // Transaction limit
    // Step 1: Create DP Array
    vector<vector<vector<int>>> dp(prices.size() + 1, vector<vector<int>>(2, vector<int>(transactionLimit + 1, 0)));
    // Step 2: Base Case
    // Step 3: Bottom Up Approach
    for (int i=prices.size()-1; i>=0; i--) {
        for (int isHolding=0; isHolding<2; isHolding++) {
            for (int limit=1; limit<=transactionLimit; limit++) {

                int buyResult = 0, sellResult = 0;
                // Buy Stock
                if (isHolding == 0) {
                    // Buy Stock
                    int buy = dp[i + 1][1][limit] - prices[i];
                    // Skip buying
                    int skip = dp[i + 1][isHolding][limit];

                    buyResult = max(buy, skip);
                }
                // Sell Stock
                else {
                    // Sell Stock
                    int sell = dp[i + 1][0][limit - 1] + prices[i];
                    // Skip selling
                    int skip = dp[i + 1][isHolding][limit];

                    sellResult = max(sell, skip);
                }

                dp[i][isHolding][limit] = max(buyResult, sellResult);

            }
        }
    }

    return dp[0][0][2];
}

int mp2SO(vector<int>& prices) {
    int transactionLimit = 2;      // Transaction limit
    // Step 1: Create variables
    vector<vector<int>> nextRow(2, vector<int>(3, 0));
    vector<vector<int>> currRow(2, vector<int>(3, 0));

    // Step 2: Base Case
    // Step 3: Bottom Up Approach
    for (int i=prices.size()-1; i>=0; i--) {
        for (int isHolding=0; isHolding<2; isHolding++) {
            for (int limit=1; limit<=transactionLimit; limit++) {

                int buyResult = 0, sellResult = 0;
                // Buy Stock
                if (isHolding == 0) {
                    // Buy Stock
                    int buy = nextRow[1][limit] - prices[i];
                    // Skip buying
                    int skip = nextRow[isHolding][limit];

                    buyResult = max(buy, skip);
                }
                // Sell Stock
                else {
                    // Sell Stock
                    int sell = nextRow[0][limit - 1] + prices[i];
                    // Skip selling
                    int skip = nextRow[isHolding][limit];

                    sellResult = max(sell, skip);
                }
                currRow[isHolding][limit] = max(buyResult, sellResult);
            }
        }
        nextRow = currRow;
    }

    return currRow[0][2];
}

int maxProfit2(vector<int>& prices) {
    // Recursion Solution
    /*
    return mp2Rec(prices, 0, 0, 2);
    */

    // Memoization Solution
    /*
    vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(2, vector<int>(3, -1)));
    return mp2Mem(prices, 0, 0, 2, dp);
    */

    // Tabulation
    /*
    return  mp2Tab(prices);
    */

    // Space Optimization
    return mp2SO(prices);
}


// 20. Buy and Sell Stocks 4
int mp4Rec(vector<int>& prices, int i, int isHolding, int k) {
    // Base Case
    if (i >= prices.size() || k == 0) return 0;

    // Ek Case
    int buyResult = 0, sellResult = 0;
    // Buy Stock
    if (isHolding == 0) {
        // buy
        int buy = mp4Rec(prices, i + 1, 1, k) - prices[i];
        // skip
        int skip = mp4Rec(prices, i + 1, isHolding, k);
        buyResult = max(buy, skip);
    }
    // Sell Stock
    else {
        // sell
        int sell = mp4Rec(prices, i + 1, 0, k - 1) + prices[i];
        // skip
        int skip = mp4Rec(prices, i + 1, isHolding, k);
        sellResult = max(sell, skip);
    }

    return max(buyResult, sellResult);
}

int mp4Mem(vector<int>& prices, int i, int isHolding, int k, vector<vector<vector<int>>> &dp) {
    // Base Case
    if (i >= prices.size() || k == 0) return 0;

    // DP Case
    if (dp[i][isHolding][k] != -1) return dp[i][isHolding][k];

    // Ek Case
    int buyResult = 0, sellResult = 0;
    
    if (isHolding == 0) {
        // buy
        int buy = mp4Mem(prices, i + 1, 1, k, dp) - prices[i];
        // skip
        int skip = mp4Mem(prices, i + 1, isHolding, k, dp);
        buyResult = max(buy, skip);
    }
    else {
        // sell
        int sell = mp4Mem(prices, i + 1, 0, k - 1, dp) + prices[i];
        // skip
        int skip = mp4Mem(prices, i + 1, isHolding, k, dp);
        sellResult = max(sell, skip);
    }

    dp[i][isHolding][k] = max(buyResult, sellResult);
    return dp[i][isHolding][k];
}

int mp4Tab(vector<int>& prices, int &k) {
    // Step 1: Create DP Array
    vector<vector<vector<int>>> dp(prices.size() + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));
    // Step 2: Base Case
    // Step 3: Bottom Up
    for (int i=prices.size()-1; i>=0; i--) {
        for (int isHolding=0; isHolding<2; isHolding++) {
            for (int limit=1; limit<=k; limit++) {

                int buyResult = 0, sellResult = 0;
    
                if (isHolding == 0) {
                    // buy
                    int buy = dp[i + 1][1][limit] - prices[i];
                    // skip
                    int skip = dp[i + 1][isHolding][limit];
                    buyResult = max(buy, skip);
                }
                else {
                    // sell
                    int sell = dp[i + 1][0][limit - 1] + prices[i];
                    // skip
                    int skip = dp[i + 1][isHolding][limit];
                    sellResult = max(sell, skip);
                }

                dp[i][isHolding][limit] = max(buyResult, sellResult);
            }
        }
    }

    return dp[0][0][k];
}

int mp4SO(vector<int>& prices, int &k) {
    // Step 1: Variables
    vector<vector<int>> currRow(2, vector<int>(k + 1, 0));
    vector<vector<int>> nextRow(2, vector<int>(k + 1, 0));

    // Step 3: Bottom Up Approach
    for (int i=prices.size()-1; i>=0; i--) {
        for (int isHolding=0; isHolding<2; isHolding++) {
            for (int limit=1; limit<=k; limit++) {

                int buyResult = 0, sellResult = 0;
    
                if (isHolding == 0) {
                    // buy
                    int buy = nextRow[1][limit] - prices[i];
                    // skip
                    int skip = nextRow[isHolding][limit];
                    buyResult = max(buy, skip);
                }
                else {
                    // sell
                    int sell = nextRow[0][limit - 1] + prices[i];
                    // skip
                    int skip = nextRow[isHolding][limit];
                    sellResult = max(sell, skip);
                }

                currRow[isHolding][limit] = max(buyResult, sellResult);
            }
        }

        nextRow = currRow;
    }

    return currRow[0][k];
}

int maxProfit(int k, vector<int>& prices) {
    // Recursion Solution
    /*
    return mp4Rec(prices, 0, 0, k);
    */
    // Memoization Solution
    /*
    vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(2, vector<int>(k + 1, -1)));
    return mp4Mem(prices, 0, 0, k, dp);
    */
    // Tabulation Solution
    /*
    return mp4Tab(prices, k);
    */
    // Space Optimization Solution
    return mp4SO(prices, k);
}



int main() {

    

    return 0;
}