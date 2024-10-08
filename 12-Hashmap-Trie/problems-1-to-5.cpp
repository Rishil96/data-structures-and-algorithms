#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

struct Node
{
    int data;
    struct Node* next;

    Node(int x){
        data = x;
        next = NULL;
    }

};

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


// 4. Array subset of another array
bool arrSubset(vector<int> arr1, vector<int> arr2) {
    // Step 1: Create a map consisting of all elements of arr2
    unordered_map<int, bool> mp;
    for (auto num: arr2) mp[num] = 1;

    // Step 2: Check all elements of arr1 if its present in map
    for (auto num: arr1) {
        if (!mp[num]) return false;
    }

    return true;
}


// 5. Union of 2 linked list
struct Node* makeUnion(struct Node* head1, struct Node* head2) {
    // Step 1: Create map and store all values
    map<int, bool> mp;
    while (head1) {
        mp[head1 -> data] = 1;
        head1 = head1 -> next;
    }
    
    while (head2) {
        mp[head2 -> data] = 1;
        head2 = head2 -> next;
    }
    
    // Step 2: Build new sorted list
    struct Node* head = NULL;
    struct Node* tail = head;
    
    for (auto it: mp) {
        int val = it.first;
        if (!head) {
            head = new struct Node(val);
            tail = head;
        }
        else {
            tail -> next = new struct Node(val);
            tail = tail -> next;
        }
    }
    
    return head;
}



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

    cout << "Array Subset of another array: " << arrSubset(vector<int>{1, 2, 3}, vector<int>{1, 2, 3, 4, 5}) << endl;
    cout << "Array Subset of another array: " << arrSubset(vector<int>{1, 2, 6}, vector<int>{1, 2, 3, 4, 5}) << endl;
    cout << "Array Subset of another array: " << arrSubset(vector<int>{1}, vector<int>{1, 2, 3}) << endl;

    return 0;
}