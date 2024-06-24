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


// 18. Remove duplicates from sorted array
int removeDuplicates(vector<int>& nums) {
    // Use index to traverse the array and find duplicates
    int index = 1;

    while (index < nums.size()) {
        // Always compare with the previous element, if both are same erase current element
        if (nums[index] == nums[index - 1]) nums.erase(nums.begin() + index);
        // Else increment index
        else index++;
    }

    // Return size of array with only unique values
    return nums.size();
}


// 19. Maximum Average Subarray
double findMaxAverage(vector<int>& nums, int k) {
    // Variable to store max average
    double maxAverage = INT_MIN;

    // Create 2 variables that will act as a window of size k
    int left = 0;
    int right = left + k - 1;

    // Keep track of the current window sum of size k
    double windowSum = 0;
    for (int i=left; i<=right; i++) windowSum += nums[i];

    // Process first window
    maxAverage = windowSum / k;
    windowSum -= nums[left];
    left++;
    right++;

    while (right < nums.size()) {
        
        // Add the new window element in windowSum
        windowSum += nums[right++];

        // Calculate new average and update and max average
        double currAverage = windowSum / k;
        maxAverage = max(maxAverage, currAverage);

        // Remove older window element from windowSum
        windowSum -= nums[left];
        left++;
    }

    // Return max average
    return maxAverage;
}


int main() {

    

    return 0;
}