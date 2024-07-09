#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
using namespace std;

// 21. Remove duplicates in string 2
string removeDuplicates(string s, int k) {
    // Use stack to store char and its adjacent count
    stack<pair<char, int>> st;

    // Loop through all characters in s
    for(int i=0; i<s.size(); ++i) {
        /* 
            If stack is not empty and current char is equal to prev char i.e. top char in stack
            simply update the count in that same top element and push it back. Only time we don't
            push the top element back is when the adjacent count reaches k
        */
        if(!st.empty() && st.top().first == s[i]){
            pair<char, int> temp = st.top();
            st.pop();
            if(temp.second < k - 1) st.push({temp.first, temp.second + 1});
        }
        /* 
            Push a new element in stack with count 1 if stack is empty or prev element is not the same
            as current element
        */
        else st.push({s[i], 1});
    }
    
    // Form the output string using the stack
    string res;

    while(!st.empty()){
        // Add the same element till its count reaches 0
        // PTR: using concatenation of strings i.e. output += st.top().first will cause MLE error
        // Better is to use push_back and then reverse the final answer
        while(st.top().second--)
            res += st.top().first;
        st.pop();
    }
    
    reverse(res.begin(), res.end());
    return res;
}


// 22. Number of laser beams in a bank
int numberOfBeams(vector<string>& bank) {
    int laserCount = 0;         // Keep track of total lasers
    int prevRow = 0;            // Keep count of security devices in previous row initiatlly 0

    // Update prevRow with the number of security devices
    for (auto r: bank[0]) if (r == '1') prevRow++;

    // Loop from row 1 to row n
    for (int i=1; i<bank.size(); i++) {
        // Get the count of security devices on current row
        int currRow = 0;
        for (auto r: bank[i]) if (r == '1') currRow++;

        // If there are security devices on current row, update laser count and set curr row to prev row
        if (currRow) {
            laserCount += (prevRow * currRow);
            prevRow = currRow;
        } 
    }

    return laserCount;
}


int main() {

    

    return 0;
}