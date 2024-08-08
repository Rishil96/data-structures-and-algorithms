#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// 11. Celebrity Problem
int celebrity(vector<vector<int> >& mat) {
    // Step 1: Add all persons to stack
    stack<int> persons;
    for (int i=0; i<mat.size(); i++) persons.push(i);
    
    // Step 2: Pop 2 persons out each iteration and check if they know each other
    while (persons.size() > 1) {
        int personA = persons.top(); persons.pop();
        int personB = persons.top(); persons.pop();
        
        // If A knows B then add B back to stack
        if (mat[personA][personB]) persons.push(personB);
        // If B knows A then add A back to stack
        else if (mat[personB][personA]) persons.push(personA);
    }
    
    // Now, only one person will remain in the stack after step 2
    // Step 3: Verify if last person remaining is a celebrity or not
    int candidate = persons.top();
    
    for (int i=0; i<mat.size(); i++) {
        // Check if candidate knows anyone, if yes its not a celebrity
        if (mat[candidate][i] == 1) return -1;
        // Check if everyone knows candidate, if no its not a celebrity
        if (i != candidate && mat[i][candidate] == 0) return -1;
    }
    
    return candidate;
}


// 12. Online Stock Span
class StockSpanner {
public:
    // First of pair is value of stock for a given day and second value is the span for that day
    stack<pair<int, int>> st;
    StockSpanner() {    
    }
    
    int next(int price) {
        int span = 1;
        // Edge Case: Where stack is empty
        if (st.empty()) {
            st.push({price, span});
            return span;
        }

        // When previous values for stocks exist
        while (!st.empty() && price >= st.top().first) {
            // Add the span of previous price that was less than or equal to current price and remove it from stack
            auto prevItem = st.top(); st.pop();
            span += prevItem.second;
        }
        st.push({price, span});
        return span;
    }
};


// 13.


// 14.


// 15.



int main() {

    

    return 0;
}