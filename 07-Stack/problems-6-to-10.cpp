#include <iostream>
#include <stack>
using namespace std;

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


// 7.


// 8.


// 9.


// 10.


int main() {

    

    return 0;
}