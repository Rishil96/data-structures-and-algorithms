#include <iostream>
#include <map>
#include <vector>
using namespace std;

// 6. Palindromic Substrings
int expand(string &s, int left, int right) {
    // Keep count of palindromes
    int counter = 0;

    // Expand current substring from given indexes
    while (left >= 0 && right < s.size()) {
        // Expand and increment count if current range forms a palindrome
        if (s[left] == s[right]) {
            counter++;
            left--;
            right++;
        }
        // If current 2 characters are not equal, break
        else break;
    }

    return counter;
}

int countSubstrings(string s) {
    // Keep count of palindromic substrings
    int ans = 0;

    // Loop through each index of s
    for (int i=0; i<s.size(); i++) {
        // Find odd length palindromes
        ans += expand(s, i, i);
        // Find even length palindromes
        ans += expand(s, i, i+1);
    }

    return ans;
}


// 7. Valid Anagrams
bool isAnagram(string s, string t) {
    // Strings of different size can never be anagrams
    if (s.size() != t.size()) return false;

    // Keep count of each character from s
    map<char, int> mp;
    for (auto ch: s) mp[ch]++;

    // Subtract from mp for each character present in t
    for (auto ch: t) {
        if (mp[ch] <= 0) return false;
        mp[ch]--;
    }

    return true;
}


// 8. Reverse only letters
bool isAlpha(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

string reverseOnlyLetters(string s) {
    // 2 pointer approach to reverse letters
    int left = 0;
    int right = s.size() - 1;

    while (left < right) {
        // Swap if both characters are letters
        if (isAlpha(s[left]) && isAlpha(s[right])) {
            swap(s[left++], s[right--]);
        }
        // If only left character is a letter, decrement right
        else if (isAlpha(s[left])) right--;
        // If only right character is a letter, increment left
        else left++;
    }

    return s;
}


// 9. Longest Common Prefix
string longestCommonPrefix(vector<string>& strs) {
    // Keep track of prefix
    string prefix;

    // Use first string as template
    string temp = strs[0];

    // Loop through all strings
    for (int i=0; i<temp.size(); i++) {
        // Use bool to see if current character is a prefix
        bool isPrefix = true;
        for (int j=1; j<strs.size(); j++) {
            // If current index of other string is not equal to template string, break
            if (temp[i] != strs[j][i]) {
                isPrefix = false;
                break;
            }
        }
        // If isPrefix is true it means all strings had their current element equal to temp
        if (isPrefix) prefix.push_back(temp[i]);
        else break;
    }

    return prefix;
}


// 10.



int main() {

    

    return 0;
}