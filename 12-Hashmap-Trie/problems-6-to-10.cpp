#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class TrieNode
{
public:
    char data;
    TrieNode* children[26];
    bool isTerminal;

    TrieNode(char _data) {
        this -> data = _data;
        for (int i=0; i<26; i++) {
            this -> children[i] = NULL;
        }
        this -> isTerminal = false;
    }
};


// 6. Intersection of 2 lists
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    unordered_map<ListNode*, bool> mp;
    
    // Add all nodes of headA in map
    while (headA) {
        mp[headA] = 1;
        headA = headA -> next;
    }

    // Check if headB element exists in headA and return the first such element
    while (headB) {
        if (mp[headB]) return headB;
        headB = headB -> next;
    }

    return NULL;
}


// 7. Sum equals to sum
bool findPairs(vector<int>& arr) {
    
    map<int, bool> mp;
    int n = arr.size();
    
    // Store all sum pairs
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            int sum = arr[i] + arr[j];
            // If current sum was already found before, it means pair exists that add upto current sum
            if (mp.find(sum) != mp.end()) {
                return true;
            }
            else {
                mp[sum] = true;
            }
        }
    }
    
    return false;
}


// 8. Largest Subarray with 0 sum
int maxLen(vector<int>& arr, int n) {
    
    map<int, int> mp;
    mp[0] = -1;
    int sum = 0;
    int ans = 0;
    
    for (int i=0; i<n; i++) {
        sum += arr[i];
        
        if (mp.find(sum) != mp.end()) {
            ans = max(ans, i - mp[sum]);
        }
        else {
            mp[sum] = i;
        }
    }
    
    return ans;
}


// 9. Largest Subarry of 0s and 1s
int maxLen(int arr[], int N)
{
    int sum = 0;
    int ans = 0;
    map<int, int> mp;
    
    for (int i=0; i<N; i++) {
        // Add as per 0 or 1 in sum
        if (arr[i] == 1) sum++;
        else sum--;
        
        // If current sum is zero add it in answer
        if (sum == 0) ans = max(ans, i + 1);
        /*  
            Else find if current sum exists 
            the subarray from current sum to current sum in past will add to 0
            Suppose, we got sum equal to -1 at index 1, and again we got sum equal to -1 at index 5
            it means the subarray between indexes 1 and 5 had sum equal to 0 as the sum remained the same.
        */
        else {
            if (mp.find(sum) != mp.end()) {
                ans = max(ans, i - mp[sum]);
            }
            else mp[sum] = i;
        }
    }
    
    return ans;
}


// 10. Replace Words
void insertWord(TrieNode* root, string word) {
    // Base Case
    if (word.size() == 0) {
        root -> isTerminal = true;
        return ;
    }

    // Ek Case
    char currChar = word[0];
    int index = currChar - 'a';

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

string getRoot(string &word, TrieNode* root) {
    string answer;
    bool isRoot = false;
    TrieNode* temp = root;
    for (int i=0; i<word.size(); i++) {
        char currChar = word[i];
        int index = currChar - 'a';

        if (temp -> children[index]) {
            temp = temp -> children[index];
            answer += currChar;
            if (temp -> isTerminal) {
                isRoot = true;
                break;
            }
        }
        else break;
    }

    return isRoot ? answer : word;
}

string replaceWords(vector<string>& dictionary, string sentence) {
    // Step 1: Build a Trie Data structure using dictionary
    TrieNode* root = new TrieNode('-');
    for (auto word: dictionary) {
        insertWord(root, word);
    }

    // Step 2: Split the words in sentence
    vector<string> words;
    string temp;

    for (int i=0; i<sentence.size(); i++) {
        if (sentence[i] == ' ') {
            words.push_back(temp);
            temp.clear();
        }
        else {
            temp += sentence[i];
            if (i == sentence.size() - 1) words.push_back(temp);
        }
    }

    // Step 3: Using all words build answer
    string ans;
    for (auto word: words) {
        string rootWord = getRoot(word, root);
        ans += rootWord + " ";
    }
    // Remove extra space from the end
    ans.pop_back();
    return ans;
}



int main() {

    

    return 0;
}