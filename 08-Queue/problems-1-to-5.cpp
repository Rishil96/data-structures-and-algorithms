#include <iostream>
#include <queue>
#include <vector>
using namespace std;


// 1. Reverse a queue
void revHelper(queue<int> &q) {
    // Base Case
    if (q.empty()) return ;
    
    // EK Case
    int frontElement = q.front();
    q.pop();
    revHelper(q);
    q.push(frontElement);
    
    return ;
}

queue<int> rev(queue<int> q)
{
    // add code here.
    revHelper(q);
    return q;
}


// 2. Reverse first k elements of queue
void reverseK(queue<int>& q, int &k) {
    // Base Case
    if (q.empty() || k == 0) return ;
    
    // Ek Case
    int front = q.front(); q.pop();
    k--;
    reverseK(q, k);
    q.push(front);
    
    return ;
}

// Function to reverse first k elements of a queue.
queue<int> modifyQueue(queue<int> q, int k) {
    // Get count of size - k elements
    int remaining = q.size() - k;
    // Reverse k elements and put it at end of stack
    reverseK(q, k);
    
    // Reset back remaining elements to original position
    for (int i=0; i<remaining; i++) {
        int front = q.front(); q.pop();
        q.push(front);
    }
    
    return q;
}


// 3. Interleave the first half of the queue with second half
vector<int> rearrangeQueue(queue<int> &q){
    // Add first half of current queue in another queue
    queue<int> first;
    int size = q.size() / 2;
    for (int i=0; i<size; i++) {
        first.push(q.front()); 
        q.pop();
    }
    
    // Build answer by using elements from both queues one by one
    vector<int> ans;
    while (!first.empty() && !q.empty()) {
        ans.push_back(first.front()); first.pop();
        ans.push_back(q.front()); q.pop();
    }
    
    return ans;
}


// 4. First non repeating character in a stream
string FirstNonRepeating(string A){
    string ans;             // Answer var
    int freq[26] = {0};     // Frequency of letters
    queue<char> q;          // Store first repeating
    
    for (auto letter: A) {
        // Update freq of current letter
        freq[letter - 'a']++;
        if (freq[letter - 'a'] == 1) q.push(letter);
        // Remove repeating letters from queue
        while (!q.empty() && freq[q.front() - 'a'] > 1) q.pop();
        
        // Write answer for current position
        if (q.empty()) ans.push_back('#');
        else ans.push_back(q.front());
    }
    
    return ans;
}


// 5. Gas station



int main() {

    

    return 0;
}