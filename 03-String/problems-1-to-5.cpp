#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 1. Valid Palindrome
bool isAlphaNum(char ch) {
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'));
}

bool isPalindrome(string s) {
    int leftIndex = 0;
    int rightIndex = s.size() - 1;

    while (leftIndex < rightIndex) {
        // Get left and right characters to compare for palindrome
        int leftChar = s[leftIndex];
        int rightChar = s[rightIndex];

        // Handle non-alphanumeric characters on left
        if (!isAlphaNum(leftChar)) {
            leftIndex++;
        }
        // Handle non-alphanumeric characters on right
        else if (!isAlphaNum(rightChar)) {
            rightIndex--;
        }
        // Compare both left and right in lower case format
        else {
            leftChar = (leftChar >= 'A' && leftChar <= 'Z') ? leftChar + 32 : leftChar;
            rightChar = (rightChar >= 'A' && rightChar <= 'Z') ? rightChar + 32 : rightChar;
            if (leftChar != rightChar) return false;
            leftIndex++;
            rightIndex--;
        }
    }

    return true;
}


// 2. Remove all adjacent duplicates in string 
string removeDuplicates(string s) {
    // Build answer with no duplicates by stack mechanism
    string ans;
    for (int i=0; i<s.size(); i++) {
        // If current element is already in answer's last index, it means these are duplicate pairs, remove last element from answer
        if (ans.size() > 0 && ans.back() == s[i]) ans.pop_back();
        // If above condition is not true it means there is no duplicate, add it in answer
        else ans.push_back(s[i]);
    }

    return ans;
}


// 3. Remove all occurrences of a substring
string removeOccurrences(string s, string part) {
    // Find occurrence of substring in main string
    auto found = s.find(part);
    // While we keep on finding part in s, keep erasing it and find the part in s again
    while (found != string :: npos) {
        s.erase(found, part.size());
        found = s.find(part);
    }
    // Return s after removing all occurrences of part
    return s;
}


// 4. Valid Palindrome 2
// Helper function to check palindrome
bool isPal(string &s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

bool validPalindrome(string s) {
    int leftIndex = 0;
    int rightIndex = s.size() - 1;

    while (leftIndex < rightIndex) {
        // If left and right character matches then continue
        if (s[leftIndex] == s[rightIndex]) {
            leftIndex++;
            rightIndex--;
        }
        // Else try by skipping left and right element once and see if we can make a palindrome
        else {
            return isPal(s, leftIndex+1, rightIndex) || isPal(s, leftIndex, rightIndex - 1);
        }
    }

    return true;
}


// 5. Minimum Time Difference
int findMinDifference(vector<string>& timePoints) {
    // Step 1: Convert all time to minutes and store it in array
    vector<int> minutesArray;
    for (int i=0; i<timePoints.size(); i++) {
        int hours = stoi(timePoints[i].substr(0, 2));
        int minutes = stoi(timePoints[i].substr(3, 2));
        minutesArray.push_back((hours * 60) + minutes);
    }

    // Step 2: Sort the minutes array
    sort(minutesArray.begin(), minutesArray.end());

    // Step 3: Find minimum time in minutes between adjacent elements as we have sorted it
    int minTimeDiff = INT_MAX;

    for (int i=1; i<minutesArray.size(); i++) {
        minTimeDiff = min(minTimeDiff, minutesArray[i] - minutesArray[i-1]);
    }

    // Step 4: Handle circular nature of a clock meaning 00:00 is also 24:00
    minTimeDiff = min(minTimeDiff, (minutesArray[0] + 1440) - minutesArray.back());

    return minTimeDiff;
}


int main() {

    

    return 0;
}