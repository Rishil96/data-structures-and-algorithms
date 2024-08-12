#include <iostream>
#include <stack>
using namespace std;

// 21. Remove k digits
string removeKdigits(string num, int k) {
    // Variable on which we will build answer
    string ans;

    // Loop through the num string
    for (int i=0; i<num.size(); i++) {
        // If answer is not empty, keep checking if last digit is answer is greater than current digit
        // If yes then pop the greater element from answer till k > 0 and then push current element
        while (!ans.empty() && num[i] < ans.back() && k > 0) {
            ans.pop_back();
            k--;
        }
        // If answer is empty, don't add leading 0
        if (ans.empty() && num[i] == '0') continue;
        ans.push_back(num[i]);
    }

    // Remove remaining k extra elements 
    while (k > 0 && !ans.empty()) {
        k--;
        ans.pop_back();
    }
    // Return answer
    return ans.empty() ? "0" : ans;
}


// 22. Minimum addition to make parentheses valid
int minAddToMakeValid(string s) {
    // Stack to remove already existing valid parentheses
    stack<char> st;

    // Loop through the string
    for (auto ch: s) {
        // Add opening bracket in string
        if (ch == '(') st.push(ch);
        // Closing bracket case
        else {
            // If top of stack has opening bracket then pop it or else add the closing bracket in stack
            if (!st.empty() && st.top() == '(') st.pop();
            else st.push(ch);
        }
    }

    // Number of remaining brackets in stack will be the number we have to add to make parentheses valid
    return st.size();
}


// 23. Design Browser History
class BrowserHistory {
public:
    // Maintain 2 stacks to keep track of both back and forward history
    // Top url of backHistory will be the current url our browser is on
    stack<string> backHistory;
    stack<string> forwardHistory;

    BrowserHistory(string homepage) {
        backHistory.push(homepage);
    }
    
    void visit(string url) {
        // Add URL to top of backHistory denoting current URL the browser is on
        backHistory.push(url);
        // Clear forward history
        while (!forwardHistory.empty()) forwardHistory.pop();
    }
    
    string back(int steps) {
        // Add backHistory's top url to forward history steps times
        while (steps-- && backHistory.size() > 1) {
            forwardHistory.push(backHistory.top());
            backHistory.pop();
        }
        return backHistory.top();
    }
    
    string forward(int steps) {
        // Add forwardHistory's top to back history steps times
        while (steps-- && !forwardHistory.empty()) {
            backHistory.push(forwardHistory.top());
            forwardHistory.pop();
        }
        return backHistory.top(); 
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */



int main() {

    

    return 0;
}