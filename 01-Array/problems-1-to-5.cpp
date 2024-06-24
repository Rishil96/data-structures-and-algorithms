#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 1. Reverse an array
void reverseString(vector<char>& s) {
    // 1. Create 2 pointers to come from opposite sides of array
    int left = 0;
    int right = s.size() - 1;

    // 2. While left is smaller than right, swap the element @ left with element @ right and move both pointers closer to each other by 1
    while (left < right) {
        swap(s[left++], s[right--]);
    }
}


// 2. Find unique elements in an array with all other elements existing in pairs
int findUnique(vector<int>& arr) {
    // 1. Use answer variable to store unique element
    int ans = 0;

    // 2. Loop through the array and use XOR operation on answer using the elements
    for (auto a: arr) {
        ans = ans ^ a;
    }

    // 3. XOR operation cancels out to 0 for same elements so all duplicates will cancel each other out in XOR 
    // and only unique will remain in the ans variable
    return ans;
}


// 3. Sort Binary
void sortBinary(vector<int>& arr) {
    // 1. Use 2 pointers left to write 0s and right to write 1s in the array
    int left = 0;
    int right = arr.size() - 1;

    while (left < right) {
        if (arr[left] == 0) {
            left++;
        }
        else {
            swap(arr[left], arr[right--]);
        }
    }
}


// 4. Majority Element in an array
int majorityElement(vector<int>& nums) {
    // Bayer-Moore Voting Algorithm
    // 1. Use 2 variables, element to store majority element and count to keep the count of current element
    int element = 0;
    int count = 0;

    // 2. Loop through the array to find majority element
    for (auto n: nums) {
        // If count is 0 we set the current element as majority element
        if (count == 0) {
            count++;
            element = n;
        }
        // If current element is equal to our majority element, increment count
        else if (element == n) count++;
        // Else if current element is not equal, decrement count
        else count--;
    }

    // Note: If we find not equal elements enough times, our count will drop back to 0 and we set a new element as majority element
    return element;
}


// 5. Rotate an array by k
void rotate(vector<int>& nums, int k) {
    // Step 1: Bring k in range of size of nums array
    k = k % nums.size();
    if (k == 0) return ;
    
    // Step 2: Save k elements to be rotated in queue from end of array
    queue<int> q;
    for (int i=nums.size()-k; i<nums.size(); i++) {
        q.push(nums[i]);
    }

    // Step 3: Shift the remaining elements from the start of array to the right
    for (int i=nums.size()-k-1; i>=0; i--) {
        nums[i+k] = nums[i];
    }

    // Step 4: Overwrite the k elements from the beginning/left of array
    for (int i=0; i<k; i++) {
        int front = q.front(); q.pop();
        nums[i] = front;
    }
}


int main() {

    vector<int> arr{1, 2, 3, 3, 2, 1, 4, 5, 5, 7, 6, 6, 7};
    cout << "Find Unique: " << findUnique(arr) << endl;

    vector<int> arr2{1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0};
    sortBinary(arr2);
    cout << "Sort Binary: ";
    for (auto a: arr2) cout << a << " ";
    cout << endl;

    return 0;
}