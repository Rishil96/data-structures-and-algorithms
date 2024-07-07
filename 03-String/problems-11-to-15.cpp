#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// 11. Isomorphic Strings
bool isIsomorphic(string s, string t) {
    // Create maps to track if t characters are used for mapping and another to map s and t characters
    unordered_map<char, bool> isMapped;
    unordered_map<char, char> isoMap;

    // Start mapping s and t
    for (int i=0; i<s.size(); i++) {
        char s1 = s[i];
        char t1 = t[i];

        /* 
        If s char is not mapped to any character yet and t char is not used for mapping
        then map them together
        */
        if (isoMap.find(s1) == isoMap.end() && !isMapped[t1]) {
            isoMap[s1] = t1;
            isMapped[t1] = true;
        }
        // Either s1 already has a mapping or t1 is already used to map some character
        else {
            // If s1 is not mapped to t1 then return false
            if (isoMap[s1] != t1) return false;
        }
    }
    // Return true when all characters are mapped successfully without breaking isomorphic rule
    return true;
}


// 12. Reorganize String
int getMaxIndex(int counter[]) {
    int ansIndex = 0;

    // Update ans index when we find any new index i that has more count than ans index
    for (int i=1; i<26; i++) {
        if (counter[i] > counter[ansIndex]) ansIndex = i;
    }

    return ansIndex;
}

string reorganizeString(string s) {
    // Create a counter array to keep track of counts of each character
    int counter[26] = {0};
    for (auto ch: s) counter[ch - 'a']++;

    // Build answer in ans string using index variable
    string ans(s.size(), ' ');
    int index = 0;

    // Get character with maximum count and place it in alternating index
    int maxIndex = getMaxIndex(counter);

    // Condition to check whether valid answer is possible or not
    /* 
    If any character has count more than half of the length of string
    it means there will exist atleast one spot where we have to place same char
    next to each other
    */
    if (s.size() & 1 && counter[maxIndex] > s.size() / 2 + 1) return "";
    else if (s.size() % 2 == 0 && counter[maxIndex] > s.size() / 2) return "";

    for (int i=0; i<s.size(); i++) {
        // Get new max index if empty
        maxIndex = counter[maxIndex] == 0 ? getMaxIndex(counter) : maxIndex;
        // Add character to answer
        ans[index] = maxIndex + 'a';

        // Decrement from counter
        counter[maxIndex]--;

        // Update index
        index = (index + 2) >= s.size() ? 0 : index + 2;
        while (index < s.size() && ans[index] != ' ') index++;
    }

    return ans;
}


// 13. Group Anagrams
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    // Store answer
    vector<vector<string>> ans;

    // Find anagrams and store it in map
    unordered_map<string, vector<string>> anagrams;

    // All anagrams in sorted form will be equal to each other
    for (auto s: strs) {
        string ogString = s;
        sort(s.begin(), s.end());
        anagrams[s].push_back(ogString);
    }

    // Store all grouped anagrams in ans array
    for (auto item: anagrams) {
        ans.push_back(item.second);
    }

    return ans;
}


// 14. Longest Palindromic Substring
void expand(string& s, int left, int right, string& ans) {
    // Store longest palindrome formed from current left and right position
    string temp;

    // Expand left and right till we have valid palindrome or we go beyond valid index of s
    while (left >= 0 && right < s.size()) {
        // Store answer if current left and right boundaries make a valid palindrome
        if (s[left] == s[right]) {
            temp = s.substr(left, right - left + 1);
        }
        else {
            break;
        }
        // Expand on both sides
        left--;
        right++;
    }

    if (temp.size() > ans.size()) ans = temp;

    return ;
}

string longestPalindrome(string s) {
    // Store longest palindrome in ans
    string ans;

    // Loop through s
    for (int i=0; i<s.size(); i++) {
        // Expand and find longest palindrome for odd number
        expand(s, i, i, ans);
        // Expand and find longest palindrome for even number
        expand(s, i, i+1, ans);
    }

    return ans;
}


// 15. Find the index of first occurrence in a string
int strStr(string haystack, string needle) {
    int left = 0;
    int right = needle.size() - 1;

    while (right < haystack.size()) {
        // Match first character and if matched try all characters
        if (haystack[left] == needle[0]) {
            bool found = true;
            // Check all characters from left to right with needle
            for (int i=left; i<=right; i++) {
                if (!(haystack[i] == needle[i-left])) {
                    found = false;
                    break;
                }
            }
            // Return left as it is starting index of substring
            if (found) return left;
        }

        // Move the window
        left++;
        right++;
    }

    return -1;
}


int main() {

    

    return 0;
}