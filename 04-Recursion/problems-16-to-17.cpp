#include <iostream>
#include <vector>
using namespace std;


// 16. Minimum Cost for Tickets
int minCostHelper(vector<int>& days, vector<int>& costs, int i) {
    // Base Case
    if (i >= days.size()) return 0;

    // Ek Case
    // 1. Use 1 day pass
    int oneDayPass = costs[0] + minCostHelper(days, costs, i+1);

    // 2. Use 7 day pass
    int expiryDate = days[i] + 6;                                // Expiry as per current day
    int j = i;                                                   // Temp variable to traverse days
    while (j < days.size() && days[j] <= expiryDate) j++;        // Consume days till pass is valid
    int sevenDayPass = costs[1] + minCostHelper(days, costs, j); 

    // 3. Use 30 day pass
    expiryDate = days[i] + 29;                                   // Expiry as per current day
    j = i;                                                       // Temp variable to traverse days
    while (j < days.size() && days[j] <= expiryDate) j++;        // Consume days till pass is valid
    int thirtyDayPass = costs[2] + minCostHelper(days, costs, j);

    // Return the min ans that was found by trying all three passes
    return min(oneDayPass, min(sevenDayPass, thirtyDayPass));
}

int mincostTickets(vector<int>& days, vector<int>& costs) {
    return minCostHelper(days, costs, 0);
}


// 17. Number of Dice rolls with target sum
int MODULE = 1000000007;

int numRollsToTarget(int n, int k, int target) {
    // Base Case 1: A combination of dice was found and target got to 0
    if (n == 0 && target == 0) return 1;

    // Base Case 2: Combination fails if target goes below 0
    if (n < 0 || target < 0) return 0;

    // Ek Case
    int totalWays = 0;

    // Roll dice
    for (int face=1; face<=k; face++) {
        // Calculate answer by subtracting current face value from target
        int ans = numRollsToTarget(n - 1, k, target - face) % MODULE;
        // Add it to main answer and calculate module
        totalWays = (totalWays % MODULE) + (ans % MODULE);
    }

    return totalWays;
}



int main() {

    

    return 0;
}