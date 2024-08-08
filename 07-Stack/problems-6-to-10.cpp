#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// 6. Longest Valid Parentheses
int longestValidParentheses(string s) {
    // Use stack to keep track of indexes and push -1 to denote start of string
    stack<int> indexes;
    indexes.push(-1);
    int maxValidPar = 0;

    for (int i=0; i<s.size(); i++) {
        // Opening Bracket Process
        if (s[i] == '(') {
            indexes.push(i);
        }
        // Closing Bracket Process
        else {
            // Cancel out current closing bracket with opening bracket index inside stack
            indexes.pop();
            // Calculate max valid parentheses if stack is not empty meaning there was a valid opening bracket for current closing bracket
            if (!indexes.empty()) {
                maxValidPar = max(maxValidPar, i - indexes.top());
            }
            // Here a valid parentheses was not made for current closing bracket, so make this index as starting point to find next valid parentheses
            else indexes.push(i);
        }
    }

    return maxValidPar;
}


// 7. Largest Rectangle in a Histogram
vector<int> getPSI(vector<int>& heights) {
    vector<int> ans(heights.size(), -1);            // Initialize answer array
    stack<int> st;                                  // Use stack to get prev smaller index
    st.push(-1);                                    // For first height 0th index, prev smaller index will be -1

    for (int i=0; i<heights.size(); i++) {
        // Remove from stack till top element at stack is greater than our current element
        while (!st.empty() && st.top() != -1 && heights[i] <= heights[st.top()]) {
            st.pop();
        }

        // Push top index if stack is not empty
        if (!st.empty()) ans[i] = st.top();
        // Push current index in stack for future heights
        st.push(i);
    }

    return ans;
}

vector<int> getNSI(vector<int>& heights) {
    vector<int> ans(heights.size(), heights.size());
    stack<int> st;
    st.push(heights.size());

    for (int i=heights.size()-1; i>=0; i--) {
        // Remove from stack till top element at stack is greater than our current element
        while (!st.empty() && st.top() != heights.size() && heights[i] <= heights[st.top()]) {
            st.pop();
        }

        // Push top index of stack if its not empty
        if (!st.empty()) ans[i] = st.top();
        // Push current index for future heights
        st.push(i);
    }

    return ans;
}

int largestRectangleArea(vector<int>& heights) {
    // Get next smaller and previous smaller indexes of every bar
    vector<int> nextSmallerIndex = getNSI(heights);
    vector<int> prevSmallerIndex = getPSI(heights);

    // Store max area in this variable
    int area = INT_MIN;

    for (int i=0; i<heights.size(); i++) {
        // Calculate area with respect to current bar of histogram
        int currArea = (nextSmallerIndex[i] - prevSmallerIndex[i] - 1) * heights[i];
        // Update max area
        area = max(area, currArea);
    }

    return area;
}


// 8. Remove all adjacent duplicates in a string
string removeDuplicates(string s) {
    // If top element of stack is not equal to current element of s, push it in stack or else pop top from stack
    stack<char> st;
    for (auto ch: s) {
        if (st.empty() || st.top() != ch) st.push(ch);
        else st.pop();
    }

    // Build answer from popping elements from stack
    string ans;
    while (!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }
    
    reverse(ans.begin(), ans.end());
    return ans;
}


// 9. Count Bracket Reversals
int countRev (string s) { 
    // Edge Case: Odd length of s can never be balanced
    if (s.size() & 1) return -1;
    
    // Use stack and remove the valid parentheses from it
    stack<char> par;
    for (auto ch: s) {
        if (ch == '{') par.push(ch);
        else {
            if (!par.empty() && par.top() == '{') par.pop();
            else par.push(ch);
        }
    }
    
    // After above loop, only invalid parentheses are left so we swap them
    int ans = 0;
    while (par.size() > 1) {
        // Get pairs of parentheses and fix them
        char right = par.top(); par.pop();
        char left = par.top(); par.pop();
        
        // If both brackets are equal, then one swap can fix them
        if (left == right) ans++;
        // If both brackets are opposite, then 2 swaps are needed
        else if (left == '}' && right == '{') ans += 2;
    }
    
    return ans;
}


// 10. Next greater node in linked list
void getNLN(ListNode* head, stack<int>& st, vector<int>& ans) {
    // Base Case
    if (!head) return ;
    
    // Recursive Call: TO reach last node first then come back to get next greater node
    getNLN(head -> next, st, ans);
    
    // Ek Case
    // Keep removing next nodes for current node if it is smaller
    while (!st.empty() && head -> val >= st.top()) st.pop();
    
    // If stack is not empty insert top element of stack in answer else insert 0
    if (!st.empty()) ans.push_back(st.top());
    else ans.push_back(0);

    // Add current node to stack to be considered as next greater node for previous nodes
    st.push(head -> val);

    return ;
}

vector<int> nextLargerNodes(ListNode* head) {
    vector<int> ans;                    // Answer variable
    stack<int> st;                      // Store next greater elements in stack
    st.push(0);                         // Push 0 initially to denote 0 as next greater element of last node
    getNLN(head, st, ans);              // Recursive call
    reverse(ans.begin(), ans.end());    // Reverse ans array as we are adding answers from last node to first

    return ans;
}


int main() {

    

    return 0;
}