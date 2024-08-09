#include <iostream>
#include <vector>
#include <stack>
#include <string>
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


// 13. Simplify Path
string simplifyPath(string path) {
    // Add directory names in stack
    stack<string> directories;
    // Use string variable to read directory names
    string currDir;

    // Go through whole path and add directory names in stack
    for (int i=0; i<path.size(); i++) {
        // If / is found it means we completed name of one directory
        if (path[i] == '/') {
            // Continue if currentDir is empty
            if (currDir.empty()) continue;
            // If currDir is .. it means to go to parent directory so pop current top of stack
            else if (currDir == "..") {
                if (!directories.empty()) directories.pop();
                currDir.clear();
            }
            // If currDir is . it means currDir so skip it
            else if (currDir == ".") {
                currDir.clear();
            }
            // Else add the directory name to stack
            else {
                directories.push(currDir);
                currDir.clear();
            }
        }
        // Build answer using characters
        else {
            currDir.push_back(path[i]);
        }
    }

    // If currDir is .., remove top directory from stack
    if (currDir == "..") {
        if (!directories.empty()) directories.pop();
    }
    // Add currDir after coming out of loop
    else if (currDir != ".") directories.push(currDir);

    string answer;

    // Build path using directories from stack
    while (!directories.empty()) {
        string topDir = directories.top(); directories.pop();
        answer = (!answer.empty()) ? topDir + "/" + answer : topDir;
    }
    
    return "/" + answer;
}


// 14. Check If Word Is Valid After Substitutions
bool isValid(string s) {
    // Use stack to check if valid word can be made
    stack<char> letters;
    int index = 0;

    while (index < s.size()) {
        // If current element is c, check if a and b are available in stack and pop them, if not return false
        if (s[index] == 'c') {
            if (letters.size() < 2) return false;
            else {
                char rTop = letters.top(); letters.pop();
                char lTop = letters.top(); letters.pop();

                if (rTop != 'b' || lTop != 'a') return false;
            }
        }
        // Push element if a or b
        else {
            letters.push(s[index]);
        }

        index++;
    }

    // Word is valid only if all elements were removed from stack
    return letters.empty();
}


// 15. Decode String
string decodeString(string s) {
    int index = 0;
    stack<string> words;

    for (auto ch: s) {
        // Add all values that are not closing bracket
        if (ch != ']') words.push(string(1, ch));
        // Process current [] when we reach closing bracket
        else {
            // Read the content inside the brackets
            string currStr;
            while (!words.empty() && words.top() != "[") {
                currStr = words.top() + currStr;
                words.pop();
            }

            // Pop opening bracket
            words.pop();

            // Read all digits first
            string currNum;
            while (!words.empty()) {
                char currDigit = words.top()[0];
                if (currDigit >= '0' && currDigit <= '9') {
                    currNum = currDigit + currNum;
                    words.pop();
                }
                else break;
            }

            // Convert currNum to integer
            int num = stoi(currNum);

            // Decode currStr using currNum
            string decodedCurrString;
            for (int i=0; i<num; i++) {
                decodedCurrString += currStr;
            }

            // Push current decoded string back to stack 
            words.push(decodedCurrString);
        }
        
        index++;
    }

    // Merge the remaining decoded words in stack
    while (words.size() > 1) {
        string word2 = words.top(); words.pop();
        string word1 = words.top(); words.pop();
        words.push(word1 + word2);
    }

    return words.top();
}


int main() {

    

    return 0;
}