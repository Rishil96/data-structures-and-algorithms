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

// Search Word
bool searchWord(TrieNode* root, string word) {
    // Base Case
    if (word.size() == 0) {
        return root -> isTerminal;
    }

    // Ek Case 
    char ch = word[0];
    int index = ch - 'a';

    return (root -> children[index] != NULL) ? searchWord(root -> children[index], word.substr(1)) : false;
}


int main() {

    TrieNode* root = new TrieNode('\0');
    insertWord(root, "rishil");
    insertWord(root, "ashwin");
    cout << "Search Word rishil: " << searchWord(root, "rishil") << endl;
    cout << "Search Word levi: " << searchWord(root, "levi") << endl;
    cout << "Search Word ashwin: " << searchWord(root, "ashwin") << endl;
    deleteWord(root, "rishil");
    cout << "Search Word rishil after deletion: " << searchWord(root, "rishil") << endl;

    return 0;
}