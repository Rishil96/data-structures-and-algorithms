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


// 31. Unique Binary Search Trees 2
vector<TreeNode*> gtRec(int start, int end) {
    // Base Case 1
    if (start > end) return {0};
    // Base Case 2
    if (start == end) return {new TreeNode(start)};

    // Ek Case
    vector<TreeNode*> answer;
    // Loop from start to end to use each number as root
    for (int root=start; root<=end; root++) {
        // Recursive Case: Get answers from left and right of root
        vector<TreeNode*> leftAns = gtRec(start, root - 1);
        vector<TreeNode*> rightAns = gtRec(root + 1, end);

        // Loop through each of the left and right answer vectors and build unique trees
        for (int left=0; left<leftAns.size(); left++) {
            for (int right=0; right<rightAns.size(); right++) {
                
                // Create root node
                TreeNode* rootNode = new TreeNode(root);
                // Attach left child and right child
                rootNode -> left = leftAns[left];
                rootNode -> right = rightAns[right];

                answer.push_back(rootNode);
            }
        }
    }

    return answer;
}

map<pair<int, int>, vector<TreeNode*>> dp;
vector<TreeNode*> gtMem(int start, int end) {
    // Base Case 1
    if (start > end) return {0};
    // Base Case 2
    if (start == end) return {new TreeNode(start)};

    // DP Case
    if (dp.find({start, end}) != dp.end()) return dp[{start, end}];

    // Ek Case
    vector<TreeNode*> answer;
    // Loop from start to end to use each number as root
    for (int root=start; root<=end; root++) {
        // Recursive Case: Get answers from left and right of root
        vector<TreeNode*> leftAns = gtMem(start, root - 1);
        vector<TreeNode*> rightAns = gtMem(root + 1, end);

        // Loop through each of the left and right answer vectors and build unique trees
        for (int left=0; left<leftAns.size(); left++) {
            for (int right=0; right<rightAns.size(); right++) {
                
                // Create root node
                TreeNode* rootNode = new TreeNode(root);
                // Attach left child and right child
                rootNode -> left = leftAns[left];
                rootNode -> right = rightAns[right];

                answer.push_back(rootNode);
            }
        }
    }

    return dp[{start, end}] = answer;
}

vector<TreeNode*> generateTrees(int n) {
    // Edge Case
    if (n == 0) return {};
    // Recursion Solution
    // return gtRec(1, n);
    // Memoization Solution
    return gtMem(1, n);
}


// 32. Word Break 2
vector<string> wbRec(string &s, unordered_map<string, bool> &dict, int index) {
    // Base Case
    if (index >= s.size()) return {""};

    // Ek Case
    vector<string> ans;
    string word;

    for (int i=index; i<s.size(); i++) {
        word.push_back(s[i]);                           // Push current character in word
        if (dict.find(word) == dict.end()) continue;    // If not a word in dict then continue

        vector<string> right = wbRec(s, dict, i+1);     // Build answer from ahead using Recursion
        for (auto eachRightWord: right) {
            // Build sentence from each sentence from future answer
            string endPart;
            if (eachRightWord.size() > 0) endPart = " " + eachRightWord;
            ans.push_back(word + endPart);
        }
    }

    return ans;
}

vector<string> wordBreak(string s, vector<string>& wordDict) {
    // Create map of dictionary words
    unordered_map<string, bool> words;
    for (auto w: wordDict) words[w] = 1;
    
    // Recursion Ans
    return wbRec(s, words, 0);
}


// 33. Distinct Subsequences
int ndRec(string &s, string &t, int i, int j) {
    // Base Case 1: Full match of s and t
    if (i >= s.size() && j >= t.size()) {
        return 1;
    }
    // Base Case 2: s consumed but not fully matched with t
    if (i >= s.size()) return 0;

    // Ek Case
    int ans;
    // Current character matches for both strings
    if (s[i] == t[j]) {
        int ans1 = ndRec(s, t, i + 1, j + 1);       // Match current character
        int ans2 = ndRec(s, t, i + 1, j);           // Don't match and try to get another subseq from s
        ans = ans1 + ans2;
    }
    // Current character don't match for s and t
    else {
        ans = ndRec(s, t, i + 1, j);                // Try another subseq by moving s index ahead
    }

    return ans;
}

int ndMem(string &s, string &t, int i, int j, vector<vector<int>> &dp) {
    // Base Case 1: Full match of t
    if (j >= t.size()) return 1;
    // Base Case 2: s consumed but not fully matched with t
    if (i >= s.size()) return 0;

    // DP Case
    if (dp[i][j] != -1) return dp[i][j];

    // Ek Case
    int ans;
    // Current character matches for both strings
    if (s[i] == t[j]) {
        int ans1 = ndMem(s, t, i + 1, j + 1, dp);       // Match current character
        int ans2 = ndMem(s, t, i + 1, j, dp);           // Don't match and try to get another subseq from s
        ans = ans1 + ans2;
    }
    // Current character don't match for s and t
    else {
        ans = ndMem(s, t, i + 1, j, dp);                // Try another subseq by moving s index ahead
    }

    return dp[i][j] = ans;
}

int ndTab(string &s, string &t) {
    // Step 1: Create DP Array
    vector<vector<long long int>> dp(s.size() + 1, vector<long long int>(t.size() + 1, 0));
    // Step 2: Base Case Update
    for (int i=0; i<dp.size(); i++) dp[i][t.size()] = 1;
    // Step 3: Bottom Up Approach
    for (int i=s.size()-1; i>=0; i--) {
        for (int j=t.size()-1; j>=0; j--) {

            int ans = 0;
            // Current character matches for both strings
            if (s[i] == t[j]) {
                ans += dp[i + 1][j + 1];       // Match current character
            }
            ans += dp[i + 1][j];                // Try another subseq by moving s index ahead
            // Update answer for current i and j
            dp[i][j] = ans;
        }
    }

    return dp[0][0];
}

int numDistinct(string s, string t) {
    // Recursion Solution
    /*
    return ndRec(s, t, 0, 0);
    */
    // Memoization Solution
    /*
    vector<vector<int>> dp(s.size(), vector<int>(t.size(), -1));
    return ndMem(s, t, 0, 0, dp);
    */
    // Tabulation Solution
    return ndTab(s, t);
}


// 34.


// 35.



int main() {
    

    return 0;
}