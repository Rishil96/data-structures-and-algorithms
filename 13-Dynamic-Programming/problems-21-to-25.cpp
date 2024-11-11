#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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


// 22. House Robber 3
int robRec(TreeNode* root, bool canRob) {
    // Base Case
    if (!root) return 0;
    // Ek Case
    int rob = 0;
    if (canRob) {
        rob = root -> val + robRec(root -> left, false) + robRec(root -> right, false);
    }

    int dontRob = robRec(root -> left, true) + robRec(root -> right, true);
    return max(rob, dontRob);
}

int robMem(TreeNode* root, bool canRob, map<pair<TreeNode*, bool>, int> &dp) {
    // Base Case
    if (!root) return 0;
    // Dp Case
    if (dp.find({root, canRob}) != dp.end()) return dp[{root, canRob}];
    // Ek Case
    int rob = 0;
    if (canRob) {
        rob = root -> val + robMem(root -> left, false, dp) + robMem(root -> right, false, dp);
    }

    int dontRob = robMem(root -> left, true, dp) + robMem(root -> right, true, dp);
    dp[{root, canRob}] = max(rob, dontRob);
    return dp[{root, canRob}];
}

int robMem2(TreeNode* root, unordered_map<TreeNode*, int> &dp) {
    // Base Case
    if (!root) return 0;

    // DP Case
    if (dp.find(root) != dp.end()) return dp[root];

    // Ek Case
    int robHouse = root -> val, dontRobHouse = 0;

    // Include Case
    if (root -> left) {
        robHouse += robMem2(root -> left -> left, dp) + robMem2(root -> left -> right, dp);
    }
    if (root -> right) {
        robHouse += robMem2(root -> right -> left, dp) + robMem2(root -> right -> right, dp); 
    }
    
    dontRobHouse = robMem2(root -> left, dp) + robMem2(root -> right, dp);

    dp[root] = max(robHouse, dontRobHouse);
    return dp[root];
}

int rob(TreeNode* root) {
    // Recursion Solution
    /*
    return robRec(root, true);
    */
    // Memoization Solution
    map<pair<TreeNode*, bool>, int> dp;
    return robMem(root, true, dp);
}


// 23. Predict the Winner
int ptwRec(vector<int>& nums, int start, int end) {
    // Base Case
    if (start == end) return nums[start];

    // Ek Case
    // P1 scores nums[start] points and P2 will reduce it by choosing next
    int diffStart = nums[start] - ptwRec(nums, start + 1, end);
    // P1 scores nums[end] points and P2 will reduce it by choosing next
    int diffEnd = nums[end] - ptwRec(nums, start, end - 1);

    return max(diffStart, diffEnd);        
}

int ptwMem(vector<int>& nums, int start, int end, vector<vector<int>> &dp) {
    // Base Case
    if (start == end) return nums[start];
    // DP Case
    if (dp[start][end] != -1) return dp[start][end];
    // Ek Case 
    // P1 scores nums[start] points and P2 will reduce it by choosing next
    int diffStart = nums[start] - ptwMem(nums, start + 1, end, dp);
    // P1 scores nums[end] points and P2 will reduce it by choosing next
    int diffEnd = nums[end] - ptwMem(nums, start, end - 1, dp);

    dp[start][end] = max(diffStart, diffEnd); 
    return dp[start][end];
}

int ptwTab(vector<int>& nums) {
    // Step 1: Create DP Array
    vector<vector<int>> dp(nums.size(), vector<int>(nums.size() + 1, -1));
    // Step 2: Base Case
    for (int i=0; i<nums.size(); i++) {
        dp[i][i] = nums[i];
    }
    // Step 3: Bottom Up
    int i = nums.size();
    for (int start=nums.size()-1; start>=0; start--) {
        for (int end=i; end<nums.size(); end++) {
            int diffStart = nums[start] - dp[start + 1][end];
            int diffEnd = nums[end] - dp[start][end - 1];

            dp[start][end] = max(diffStart, diffEnd);
        }
        --i;
    }
    return dp[0][nums.size()-1];
}

bool predictTheWinner(vector<int>& nums) {
    int start = 0;
    int end = nums.size()-1;
    // Recursion Solution
    /*
    return ptwRec(nums, start, end) >= 0;
    */
    // Memoization Solution
    /*
    vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), -1));
    return ptwMem(nums, start, end, dp) >= 0;
    */
    // Tabulation Solution
    return ptwTab(nums) >= 0;
}


// 24. Word Break
bool check(string &word, vector<string>& wordDict) {
    for (auto w: wordDict) {
        if (word == w) return true;
    }
    return false;
}

bool wbRec(string &s, int i, string currWord, unordered_map<string, bool> &wordDict) {
    // Base Case
    if (i >= s.size()) {
        if (wordDict[currWord]) return true;
        return false;
    }

    // Ek Case
    currWord += s[i];

    // Recursion Case
    bool useWord = 0;
    if (wordDict[currWord] == true) {
        useWord = wbRec(s, i + 1, "", wordDict);
    }
    
    bool dontUseWord = wbRec(s, i + 1, currWord, wordDict);

    return useWord || dontUseWord;
}

bool wbMem(string &s, int i, string currWord, unordered_map<string, bool> &wordDict, map<pair<int, string>, bool> &dp) {
    // Base Case
    if (i >= s.size()) {
        if (wordDict[currWord]) return true;
        return false;
    }

    // DP Case
    if (dp.find({i, currWord}) != dp.end()) return dp[{i, currWord}];

    // Ek Case
    currWord += s[i];

    // Recursion Case
    bool useWord = 0;
    if (wordDict[currWord] == true) {
        useWord = wbMem(s, i + 1, "", wordDict, dp);
    }
    
    bool dontUseWord = wbMem(s, i + 1, currWord, wordDict, dp);

    dp[{i, currWord}] = useWord || dontUseWord;
    return dp[{i, currWord}];
}

bool wbMemoization(string &s, vector<string>& wordDict, int index, vector<int>& dp) {
    // Base Case
    if (index >= s.size()) return true;

    // DP Case
    if (dp[index] != -1) return dp[index];

    // Ek Case
    bool flag = false;
    string word = "";

    for (int i=index; i<s.size(); i++) {
        word += s[i];
        if (check(word, wordDict)) {
            flag = flag || wbMemoization(s, wordDict, i+1, dp);
        }
    }

    dp[index] = flag;
    return dp[index];
}

bool wbTab(string &s, vector<string>& wordDict) {
    // Step 1: Create DP Array
    vector<int> dp(s.size() + 1, 0);
    // Step 2: Add base case
    dp[s.size()] = 1;
    // Step 3: Bottom up
    for (int index=s.size()-1; index>=0; index--) {
        bool flag = false;
        string word = "";
        for (int i=index; i<s.size(); i++) {
            word += s[i];
            if (check(word, wordDict)) {
                flag = flag || dp[i+1];
            }
        }

        dp[index] = flag;
    }
    return dp[0];
}

bool wordBreak(string s, vector<string>& wordDict) {
    // Create map for easy access of words
    unordered_map<string, bool> words;
    for (auto w: wordDict) words[w] = 1;

    // Recursion Solution
    /*
    return wbRec(s, 0, "", words);
    */
    // Memoization Solution
    /*
    map<pair<int, string>, bool> dp;
    return wbMem(s, 0, "", words, dp);
    */
    // Memoization Solution 2
    /*
    vector<int> dp(s.size() + 1, -1);
    return wbMemoization(s, wordDict, 0, dp);
    */
    // Tabulation Solution
    return wbTab(s, wordDict);
}


// 25.



int main() {

    

    return 0;
}