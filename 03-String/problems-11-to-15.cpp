#include <iostream>
#include <unordered_map>
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


// 13.


// 14.


// 15.



int main() {

    

    return 0;
}