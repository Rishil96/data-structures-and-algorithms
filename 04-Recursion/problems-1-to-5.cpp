#include <iostream>
#include <vector>
using namespace std;

// 1. Climbing Stairs
int climbStairs(int n) {
    // Rule: we can climb 1 or 2 steps at a single time
    // Base Case: We can reach stair 1 in one ways and stair 2 in two ways i.e. climbing 1 step 2 times and climbing 2 step 1 time.
    if (n == 1 || n == 2) return n;

    // Baaki Recursion: We can find the ways to reach n steps if we know how many ways are there to reach n - 1 and n - 2 steps.
    return climbStairs(n - 1) + climbStairs(n - 2);
}


// 2. Maximize the Cuts
int maximizeTheCuts(int n, int x, int y, int z) {
    // Base Case : no segment left to cut
    if (n == 0) return 0;
    
    // Ek Case : Try to cut with x, y and z
    int ans1 = INT_MIN;
    if (n - x >= 0) ans1 = 1 + maximizeTheCuts(n - x, x, y, z);
    
    int ans2 = INT_MIN;
    if (n - y >= 0) ans2 = 1 + maximizeTheCuts(n - y, x, y, z);
    
    int ans3 = INT_MIN;
    if (n - z >= 0) ans3 = 1 + maximizeTheCuts(n - z, x, y, z);
    
    // Return the answer that took the most number of cuts
    return max(ans1, max(ans2, ans3));
}


// 3. Coin Change
int coinChange(vector<int>& coins, int amount) {
    // Base Case
    if (amount == 0) return 0;          // 0 coins are needed to make up amount 0
    if (amount < 0) return INT_MAX;     // less than 0 coins means invalid answer

    // Ek Case
    int minCoins = INT_MAX;

    // Loop through all coins and use them infinitely till we get to our target amount
    for (int i=0; i<coins.size(); i++) {
        // Find answer after using current coin
        int ans = coinChange(coins, amount - coins[i]);

        // If a valid answer was found using current coin, then update minCoins if it is lesser
        if (ans != INT_MAX && ans != -1) {
            minCoins = min(minCoins, ans + 1);
        }
    }

    // If INT_MAX was returned, it means we did not find a valid answer using given coins, return -1 
    return minCoins == INT_MAX ? -1 : minCoins;
}


// 4. House Robber
int getMaxMoney(vector<int>& nums, int index) {
    // Base Case: All houses were visited in the street
    if (index >= nums.size()) return 0;

    // Ek Case: Choose either to rob or not rob the current house
    int steal = getMaxMoney(nums, index + 2) + nums[index];
    int notSteal = getMaxMoney(nums, index + 1) + 0;

    // Return the max amount stolen whether it was from stealing or not stealing from current house
    return max(steal, notSteal);
}

int rob(vector<int>& nums) {
    return getMaxMoney(nums, 0);
}


// 5. Last Occurrence of a character using Recursion
int lastOccurrence(string &s, char key, int index) {
    /*
    Check from end of string towards the beginning
    */
    // Base Case
    if (index < 0) return -1;

    // Ek Case
    if (s[index] == key) return index;

    return lastOccurrence(s, key, index - 1);
}



int main() {
    string s = "And now the world shall feel pain... Almighty Push!";

    cout << "Last Occurrence: " << lastOccurrence(s, 'z', s.size()-1) << endl;   
    cout << "Last Occurrence: " << lastOccurrence(s, '!', s.size()-1) << endl;   
    cout << "Last Occurrence: " << lastOccurrence(s, 's', s.size()-1) << endl;   

    return 0;
}