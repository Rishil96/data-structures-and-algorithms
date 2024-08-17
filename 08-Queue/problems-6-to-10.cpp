#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
using namespace std;


// 6. Sliding Window Maximum
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> ans;
    
    // Step 1: Create a queue and process the first window in queue
    deque<int> dq;
    for (int i=0; i<k; i++) {
        // For every current element, remove all smaller elements from the back of deque
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        // Add current element index from back
        dq.push_back(i);
    }
    // Answer for first window
    ans.push_back(nums[dq.front()]);

    // Step 2: Process remaining windows
    for (int i=k; i<nums.size(); i++) {

        // Remove invalid indexes from the front of current window
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();

        // For current element, remove all smaller elements from the back
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        
        // Update answer for previous window
        ans.push_back(nums[dq.front()]);
    }

    return ans;
}


// 7. Implement queue using 2 stacks
class MyQueue {
public:
    stack<int> s1;              // Use as main queue
    stack<int> s2;              // Use it to shift elements to place new element in correct position

    MyQueue() {
        
    }
    
    void push(int x) {
        // Transfer all s1 elements to s2
        while (!s1.empty()) {
            s2.push(s1.top()); s1.pop();
        }

        // Add new element at bottom of s1
        s1.push(x);

        // Bring back all elements from s2 to s1
        while (!s2.empty()) {
            s1.push(s2.top()); s2.pop();
        }
    }
    
    int pop() {
        int popped = s1.top(); s1.pop();
        return popped;
    }
    
    int peek() {
        return s1.top();
    }
    
    bool empty() {
        return s1.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */


// 8. Implement stack using 2 queues
class MyStack {
public:
    queue<int> q1;
    queue<int> q2;

    MyStack() {
        
    }
    
    void push(int x) {
        // Move all elements of q1 to q2
        while (!q1.empty()) {
            q2.push(q1.front()); q1.pop();
        }

        // Add new element to the front
        q1.push(x);

        // Bring back all q2 elements to q1
        while (!q2.empty()) {
            q1.push(q2.front()); q2.pop();
        }
    }
    
    int pop() {
        int popped = q1.front(); q1.pop();
        return popped;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */


// 9. Sum of minimum and maximum elements of all subarrays of size k
int sumOfKSubArray(int arr[], int N, int k) {
    // Similar to sliding window maximum, use deques to process k sized windows for both minimum and maximum indexes
    deque<int> minDq;
    deque<int> maxDq;

    int sum = 0;

    // Step 1: Process first window for both min and max
    for (int i=0; i<k; i++) {
        // Max Deque Process
        while (!maxDq.empty() && arr[maxDq.back()] < arr[i]) maxDq.pop_back();
        maxDq.push_back(i);

        // Min Deque Process
        while (!minDq.empty() && arr[minDq.back()] > arr[i]) minDq.pop_back();
        minDq.push_back(i);
    }
    
    // Add min and max elements of first window in sum
    sum += (arr[maxDq.front()] + arr[minDq.front()]);

    // Step 2: Process remaining windows
    for (int i=k; i<N; i++) {
        // Max Deque Process
        // Remove invalid indexes
        while (!maxDq.empty() && maxDq.front() <= i - k) maxDq.pop_front();
        // Insert new index
        while (!maxDq.empty() && arr[maxDq.back()] < arr[i]) maxDq.pop_back();
        maxDq.push_back(i);

        // Min Deque Process
        // Remove invalid indexes
        while (!minDq.empty() && minDq.front() <= i - k) minDq.pop_front();
        // Insert new index
        while (!minDq.empty() && arr[minDq.back()] > arr[i]) minDq.pop_back();
        minDq.push_back(i);

        // Add current window sum into main ans
        sum += (arr[maxDq.front()] + arr[minDq.front()]);
    }

    return sum;
}


// 10. Recent calls
class RecentCounter {
public:
    // Queue to keep track of requests in range (t - 3000, t)
    queue<int> requests;
    RecentCounter() {
        
    }
    
    int ping(int t) {
        // Get the time difference for current request - 3000 ms
        int diff = t - 3000;
        // Remove all requests that were made before diff time
        while (!requests.empty() && requests.front() < diff) requests.pop();
        // Add current request in queue
        requests.push(t);
        // Return number of requests in range (t - 3000, t)
        return requests.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */



int main() {

    int arr[] = {2, 5, -1, 7, -3, -1, -2};
    int N = 7;
    int k = 4;

    cout << "Sum of min and max in subarrays of size k: " << sumOfKSubArray(arr, N, k) << endl;

    return 0;
}