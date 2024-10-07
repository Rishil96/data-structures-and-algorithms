#include <iostream>
using namespace std;

class TrieNode
{
    public:
        char data;                  // Current node data
        TrieNode* children[26];     // Current node's children
        bool isTerminal;            // If current node is ending of a word

        TrieNode(char _data) {
            this -> data = _data;
            for (int i=0; i<26; i++) children[i] = NULL;
            this -> isTerminal = false;
        }
};


// Insert Word
void insertWord(TrieNode* root, string word) {
    // Base Case
    if (word.size() == 0) {
        root -> isTerminal = true;
        return ;
    }

    // Ek Case
    char curr = word[0];
    int index = curr - 'a';
    
    TrieNode* child = NULL;
    if (root -> children[index]) {
        child = root -> children[index];
    }
    else {
        child = new TrieNode(curr);
        root -> children[index] = child;
    }

    insertWord(child, word.substr(1));
    return ;
}

// Delete Word
void deleteWord(TrieNode* root, string word) {
    // Base Case
    if (word.size() == 0) {
        root -> isTerminal = false;
        return ;
    }

    // Ek Case
    char curr = word[0];
    int index = curr - 'a';

    if (root -> children[index]) {
        deleteWord(root -> children[index], word.substr(1));
    }

    return ;
}


// 1. Search word in a Trie
bool searchWord(TrieNode* root, string word) {
    // Base Case
    if (word.size() == 0) {
        if (root -> isTerminal) return true;
        return false;
    }

    // Ek Case
    char currChar = word[0];
    int currIndex = currChar - 'a';

    // Check if a child exists on current index
    TrieNode* child = root -> children[currIndex];
    if (child) {
        return searchWord(child, word.substr(1));
    }
    else return false;
}

// 2. Print all words in a Trie
void printAllWords(TrieNode* root, string temp) {
    // Base Case
    if (root -> isTerminal) {
        cout << temp << " ";
    }

    // Ek Case: Loop through all children
    for (int i=0; i<26; i++) {
        TrieNode* child = root -> children[i];
        if (child) {
            printAllWords(child, temp + child -> data);
        }
    }
}

// 3. Search results as per keywords in Trie
void searchResults(TrieNode* root, string key) {
    
    TrieNode* child = root;
    // Search till keyword first
    for (auto k: key) {
        int index = k - 'a';
        if (child -> children[index]) {
            child = child -> children[index]; 
        }
        else return ;
    }

    printAllWords(child, key);
}


// 4.


// 5.



int main() {

    TrieNode* root = new TrieNode('-');
    insertWord(root, "rishil");
    insertWord(root, "ashwin");
    insertWord(root, "ramesh");
    insertWord(root, "ajitha");
    insertWord(root, "thankamani");

    cout << "Searching for rishil: " << searchWord(root, "rishil") << endl;
    cout << "Searching for ashwin: " << searchWord(root, "ashwin") << endl;
    cout << "Searching for bhageerathi: " << searchWord(root, "bhageerathi") << endl;

    insertWord(root, "bhageerathi");
    cout << "Searching for bhageerathi: " << searchWord(root, "bhageerathi") << endl;
    cout << "Searching for thankamani: " << searchWord(root, "thankamani") << endl;
    cout << "Searching for deadpool: " << searchWord(root, "deadpool") << endl;

    cout << "Printing all words in Trie: ";
    printAllWords(root, "");
    cout << endl;

    cout << "Search results: ";
    searchResults(root, "bha");
    cout << endl;

    return 0;
}