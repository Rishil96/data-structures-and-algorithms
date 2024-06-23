#include <iostream>
#include <map>
#include <vector>
using namespace std;

// 16. Key Pair
bool hasArrayTwoCandidates(int arr[], int n, int x) {
    // Use map to store numbers that exist in array
    map<int, bool> mp;
    
    // Loop through array
    for (int i=0; i<n; i++) {
        // If for current number, another number exists such that curr + another = x, return true
        if (mp[x - arr[i]]) return true;
        // Add current number in map
        mp[arr[i]] = 1;
    }
    
    return false;
}


// 17. Find Pivot Index
int pivotIndex(vector<int>& nums) {
    // While traversing the array, initially we keep left as 0 and right as sum of array elements
    int left = 0;
    int right = 0;
    for (auto n: nums) right += n;

    int ans = -1;

    // Traverse the array
    for (int i=0; i<nums.size(); i++) {
        // If sum to the left of current index and to the right of current index (excluding curr element) are equal, return curr index
        if (left == right - nums[i]) return i;
        // Else add current element to the left and subtract current element from the right
        else {
            left += nums[i];
            right -= nums[i];
        }
    }

    return ans;
}

int main() {

    

    return 0;
}