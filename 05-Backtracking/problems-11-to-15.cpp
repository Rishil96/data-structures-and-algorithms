#include <iostream>
#include <vector>
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


// 12.


// 13.


// 14.


// 15.

int main() {

    

    return 0;
}