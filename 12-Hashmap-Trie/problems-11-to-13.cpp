#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;


class TrieNode
{
public:
    char data;
    TrieNode* children[256];
    bool isTerminal;

    TrieNode(char _data) {
        this -> data = _data;
        for (int i=0; i<256; i++) {
            this -> children[i] = NULL;
        }
        this -> isTerminal = false;
    }
};


// 11. Top k frequent words
static bool cmp(pair<int, string>& a, pair<int, string>& b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    else {
        return a.first > b.first;
    }
}

vector<string> topKFrequent(vector<string>& words, int k) {
    // Step 1: Add all words in map
    unordered_map<string, int> mp;
    for (auto w: words) mp[w]++;

    // Step 2: Add all words in heap
    priority_queue<pair<int, string>> maxHeap;
    for (auto it: mp) {
        maxHeap.push({it.second, it.first});
    }

    // Step 3: Add top k words in answer array
    vector<pair<int, string>> freqAnswer;
    for (int i=0; i<words.size(); i++) {
        if (!maxHeap.empty()) {
            freqAnswer.push_back(maxHeap.top());
            maxHeap.pop();
        }
        else break;
    }

    // Step 4: Sort the answer array lexicographically
    sort(freqAnswer.begin(), freqAnswer.end(), cmp);

    // Step 5: Build final answer
    vector<string> ans;
    for (int i=0; i<k; i++) {
        ans.push_back(freqAnswer[i].second);
    }

    return ans;
}


// 12. Camelcase Matching
void insertWord(TrieNode* root, string word) {
    // Base Case
    if (word.size() == 0) {
        root -> isTerminal = true;
        return ;
    }

    // Ek Case
    char currChar = word[0];
    int index = currChar;
    cout << index << endl;

    TrieNode* child = NULL;
    if (root -> children[index]) {
        child = root -> children[index];
    }
    else {
        child = new TrieNode(currChar);
        root -> children[index] = child;
    }

    // Baaki Recursion
    insertWord(child, word.substr(1));
    return ;
}

bool isMatch(TrieNode* pattern, string word) {
    int i = 0;

    while (i < word.size()) {
        char currChar = word[i];
        int nodeIndex = currChar;

        // Case 1: Child of pattern matches with current character
        if (pattern -> children[nodeIndex]) {
            i++;
            pattern = pattern -> children[nodeIndex];
        }
        // Case 2: Match not found but since its lowercase character, we can ignore it
        else if (currChar >= 'a' && currChar <= 'z') {
            i++;
        }
        // Case 3: Matching failed
        else {
            return false;
        }
    }

    return pattern -> isTerminal;
}

vector<bool> camelMatch(vector<string>& queries, string pattern) {
    // Step 1: Create a trie for the pattern
    TrieNode* pat = new TrieNode('-');
    insertWord(pat, pattern);

    // Step 2: Loop through each queries and try to match the pattern
    vector<bool> ans(queries.size(), 0);
    
    for (int i=0; i<queries.size(); i++) {
        string currWord = queries[i];
        ans[i] = isMatch(pat, currWord);
    }

    return ans;
}


// 13. Palindrome Pairs
class TrieNode2 {
public:
    char data;
    TrieNode2* children[26];
    int stringNumber;

    TrieNode2(char ch) : data(ch), stringNumber(-1) {
        for (int i=0; i<26; i++) this -> children[i] = NULL;
    }
};

class Trie {
    
    TrieNode2* root;

    void insertUtil(TrieNode2* root, string &word, int i, int &stringNumber) {
        // Base Case
        if (i >= word.size()) {
            root -> stringNumber = stringNumber;
            return ;
        }

        // Ek Case
        int index = word[i] - 'a';

        if (!root -> children[index]) {
            root -> children[index] = new TrieNode2(word[i]);
        }

        insertUtil(root -> children[index], word, i + 1, stringNumber);
    }

public:
    Trie() {
        root = new TrieNode2('\0');
    }

    void insert(string &word, int &stringNumber) {
        insertUtil(root, word, 0, stringNumber);
    }
    
    bool isPalindrome(string &s, int low, int high) {
        while (low < high) {
            if (s[low] != s[high]) return false;
            low++;
            high--;
        }
        return true;
    }

    void searchCase2(TrieNode2* root, vector<int>& myPalindrome, string s) {
        if (root -> stringNumber != -1) {
            if (isPalindrome(s, 0, s.size() - 1)) {
                myPalindrome.push_back(root -> stringNumber);
            }
        }

        for (int i=0; i<26; i++) {
            if (root -> children[i]) {
                s.push_back(i + 'a');
                searchCase2(root -> children[i], myPalindrome, s);
                s.pop_back();
            }
        }
    }

    void search(string &word, vector<int>& myPalindrome) {
        TrieNode2* curr = root;

        // Case 1: When prefix of string word, exactly matches with a word in Trie
        for (int i=0; i<word.size(); i++) {
            int index = word[i] - 'a';
            
            if (curr -> stringNumber != -1) {
                if (isPalindrome(word, i, word.size()-1)) {
                    myPalindrome.push_back(curr -> stringNumber);
                }
            }
            
            if (curr -> children[index]) {
                curr = curr -> children[index];
            }
            else return ;
        }

        // Case 2: Search word is a prefix of the word in the trie
        searchCase2(curr, myPalindrome, "");
    }
};

vector<vector<int>> palindromePairs(vector<string>& words) {
    vector<vector<int>> ans;
    Trie trie;

    // Insert all words in reverse order and mark its string number as index of words array
    for (int i=0; i<words.size(); i++) {
        auto reverseWord = words[i];
        reverse(reverseWord.begin(), reverseWord.end());
        trie.insert(reverseWord, i);
    }

    // Find palindromic pairs of each word
    for (int i=0; i<words.size(); i++) {
        vector<int> myPalindrome; // stores palindromic pairs of ith word

        trie.search(words[i], myPalindrome);

        for (auto it: myPalindrome) {
            if (it != i) {
                ans.push_back({i, it});
            }
        }
    }

    return ans;
}


int main() {

    

    return 0;
}