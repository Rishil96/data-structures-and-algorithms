#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 11. Combination Sum 1
void getCombi(vector<int> &candidates, int &target, vector<vector<int>> &ans, vector<int>& temp, int currIndex) {
    // Base Case
    if (target == 0) {
        // If ans is empty or last combination in ans is not equal to current combination then add
        if (ans.empty() || (!ans.empty() && ans.back() != temp)) {
            ans.push_back(temp);
        }
        return ;
    }
    if (target < 0) return ;

    // Ek Case: Loop through all candidates
    for (int i=currIndex; i<candidates.size(); i++) {
        // Use current candidate to form a combination
        temp.push_back(candidates[i]);
        target -= candidates[i];
        getCombi(candidates, target, ans, temp, i);
        // Backtrack to previous state
        target += candidates[i];
        temp.pop_back();
    }

    return ;
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans;                                // Store all combinations in ans
    vector<int> temp;                                       // Store current combination
    sort(candidates.begin(), candidates.end());             // Sort combinations
    getCombi(candidates, target, ans, temp, 0);
    return ans;
}


// 12. Combination Sum 2
void getCombiII(vector<int>& candidates, int &target, vector<vector<int>>& ans, vector<int>& temp, int currIndex) {
    // Base Case
    if (target == 0) {
        ans.push_back(temp);
        return ;
    }
    if (target < 0 || currIndex >= candidates.size()) return ;

    // Ek Case
    for (int i=currIndex; i<candidates.size(); i++) {
        // Don't start a new combination if current index and previous index had the same num
        if (i > currIndex && candidates[i] == candidates[i-1]) continue;

        // Include current element in combination
        temp.push_back(candidates[i]);
        target -= candidates[i];
        currIndex++;
        // Recursive call from next index to not include current element again
        getCombiII(candidates, target, ans, temp, i+1);
        // Backtrack to previous state
        currIndex--;
        target += candidates[i];
        temp.pop_back();

    }

    return ;
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());     // Sort candidates
    vector<vector<int>> ans;                        // Store all combinations
    vector<int> temp;                               // Store current combination
    int index = 0;
    getCombiII(candidates, target, ans, temp, index);

    return ans;
}


// 13. Permutations 2
void getPerm(vector<int>& nums, vector<vector<int>>& ans, int &index) {
    // Base Case
    if (index >= nums.size()) {
        ans.push_back(nums);
        return ;
    }

    // Ek Case
    // Map to mark if a number has been placed on current index
    unordered_map<int, bool> numVis;

    for (int i=index; i<nums.size(); i++) {
        // If current number was already placed on current index then continue
        if (numVis.find(nums[i]) != numVis.end()) continue;
        // Mark current number as visited
        numVis[nums[i]] = 1;
        // Place current number at index to i and vice versa
        swap(nums[i], nums[index]);
        index++;
        getPerm(nums, ans, index);
        // Backtrack to previous state
        index--;
        swap(nums[i], nums[index]);
    }

    return ;
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> ans;
    int index = 0;
    getPerm(nums, ans, index);

    return ans;
}


// 14. Beautiful Arrangement
void findBA(int &n, int &pos, vector<bool> &numUsed, int &count) {
    // Base Case: Reaching end index means a permutation of beautiful arrangement was formed
    if (pos > n) {
        count++;
        return ;
    }

    // Ek Case: Try to place numbers from 1 to N on current position as per BA condition
    for (int num=1; num<=n; num++) {
        // Only place num if it was not used in previous index and it satisfies the BA condition
        if (!numUsed[num] && (num % pos == 0 || pos % num == 0)) {
            // Mark current number as used and increment position to start placing on next index
            numUsed[num] = 1;
            pos++;
            findBA(n, pos, numUsed, count);
            // Backtrack to previous state
            pos--;
            numUsed[num] = 0;
        }
    }
}

int countArrangement(int n) {
    int count = 0;                          // Keep count of Beautiful Arrangements
    int pos = 1;                            // Current position to place a number
    vector<bool> numUsed(n+1, false);       // Track numbers that are already placed
    findBA(n, pos, numUsed, count);         // Recursive call
    return count;
}


// 15. Distribute Repeating Integers
bool canCompleteOrder(unordered_map<int, int> &intFreq, vector<int>& quantity, int &orderIndex) {
    // Base Case
    if (orderIndex >= quantity.size()) return true;

    // Ek Case
    // Loop through integer quantites to fulfill current order
    for (auto currInt: intFreq) {
        bool ans = false;
        // If current integer frequency can fulfill current order, then fulfill it and move to next order
        if (currInt.second >= quantity[orderIndex]) {
            // Use current order number of integers from intfreq and move orderindex to next order
            intFreq[currInt.first] -= quantity[orderIndex];
            orderIndex++;
            ans = canCompleteOrder(intFreq, quantity, orderIndex);
            // If all orders are fulfilled return true
            if (ans) return ans;
            // Backtrack to previous state
            orderIndex--;
            intFreq[currInt.first] += quantity[orderIndex];
        }
    }

    return false;
}

bool canDistribute(vector<int>& nums, vector<int>& quantity) {
    // Create a frequency map that holds the frequency of each unique integer in nums
    unordered_map<int, int> intFreq;
    for (auto n: nums) intFreq[n]++;

    /* 
    Sort quantity to fulfill the highest quantity first so we can tell earlier 
    if all orders can be fulfiled
    */
    sort(quantity.rbegin(),  quantity.rend());
    int orderIndex = 0;
    return canCompleteOrder(intFreq, quantity, orderIndex);
}


int main() {

    

    return 0;
}