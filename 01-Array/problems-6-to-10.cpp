#include <iostream>
#include <vector>
using namespace std;

// 6. Buy and Sell Stock
int maxProfit(vector<int>& prices) {
    // Step 1: Use 2 variables i. profit (keeps track of max profit) and minPrice (keeps track of the minimum price encountered till date)
    int profit = INT_MIN;
    int minPrice = INT_MAX;

    // Step 2: Go through all the prices of consecutive days
    for (int i=0; i<prices.size(); i++) {
        // Update minimum price if a lower price is found
        minPrice = min(minPrice, prices[i]);
        // Calculate profit as per current date
        int currProfit = prices[i] - minPrice;

        // If current profit is more than the profit we had before, update it
        if (currProfit > profit) profit = currProfit;            
    }

    return profit;
}


// 7. Sort Colors
void sortColors(vector<int>& nums) {
    // 1. Use 3 indexes to keep track of zeros, ones and twos
    int zI = 0;                     // Holds the next index where we can place 0
    int oI = 0;                     // Used to traverse the array
    int tI = nums.size() - 1;       // Holds the next index where we can place 2

    // 2. Loop through array till all elements on right of oI is 2
    while (oI <= tI) {
        // If current element is 0, place it on zI and increment both indexes.
        if (nums[oI] == 0) {
            swap(nums[zI++], nums[oI++]);
        }
        // If current element is 1, simply move forward.
        else if (nums[oI] == 1) {
            oI++;
        }
        // If current element is 2, place it on tI and decrement tI.
        else {
            swap(nums[oI], nums[tI--]);
        }
    }
}


// 8. Move negative to left of array
void moveNegative(vector<int>& nums) {
    // 1. Use 2 pointers
    int prev = 0;       // Will be used to place negative numbers
    int curr = 0;       // Used to traverse the array

    // 2. Traverse the array
    while (curr < nums.size()) {
        if (nums[curr] < 0) {
            swap(nums[prev++], nums[curr++]);
        }
        else curr++;
    }
}


// 9. Find duplicates in array
int findDuplicate(vector<int>& nums) {
    // 1. Use Slow Fast Pointer approach from Linked List to solve this
    int slow = 0;
    int fast = 0;

    // 2. Run slow once and fast twice till they both land on same index
    do {
        slow = nums[slow];
        fast = nums[fast];
        fast = nums[fast];
    }
    while (slow != fast);

    // 3. Set slow to 0 and restart loop and move slow and fast both once
    slow = 0;
    while (nums[slow] != nums[fast]) {
        slow = nums[slow];
        fast = nums[fast];
    }

    return nums[slow];
}


// 10. Missing number
int missingNumber(vector<int>& nums) {
    // 1. Use ans variable in which we will get answer
    int ans = 0;

    // 2. Loop through entire array
    for (int i=0; i<nums.size(); i++) {
        // We will add 1 to n in ans variable using i + 1
        ans += i + 1;
        // And then subtract ans with the elements in array, in this way each element will cancel each other out except the missing number which will remain in the ans variable
        ans -= nums[i];
    }

    return ans;
}

int main() {

    vector<int> nums{1, -1, 2, -2, 3, -3, 4, -4, 5, -5};
    moveNegative(nums);

    for (auto n: nums) cout << n << " ";
    cout << endl;

    return 0;
}