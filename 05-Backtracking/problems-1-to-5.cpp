#include <iostream>
#include <vector>
using namespace std;

// 1. Permutations 1
void getPerm(vector<int>& nums, int currIndex, vector<vector<int>>& ans) {
    // Base Case
    if (currIndex >= nums.size()) {
        ans.push_back(nums);
        return ;
    }

    // Ek Case
    for (int i=currIndex; i<nums.size(); i++) {
        // Swap currIndex with i to form a new permutation
        swap(nums[currIndex], nums[i]);
        // Call Recursion for the next index
        getPerm(nums, currIndex + 1, ans);
        // Backtrack swap to retain the original array to form next permutations
        swap(nums[currIndex], nums[i]);
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> ans;
    getPerm(nums, 0, ans);
    return ans;
}


// 2. Rat in a maze
bool isValidCell(int &x, int &y, int &n, vector<vector<int>>& m, vector<vector<bool>>& isVisited) {
        // Check if new row is valid
        if (x < 0 || x >= n) return false;
        // Check if new column is valid
        if (y < 0 || y >= n) return false;
        // Check if new cell is allowed to be visited
        if (m[x][y] == 0) return false;
        // Check if new cell is not visited previously
        if (isVisited[x][y] == 1) return false;
        
        return true;
    }
    
void findPathHelper(vector<vector<int>> &m, int &n, vector<string>& paths, vector<vector<bool>>& isVisited, int &x, int &y, string &path) {

    // Base Case: Rat reached destination
    if (x == n - 1 && y == n - 1) {
        paths.push_back(path);
        return ;
    }
    
    // Ek Case
    /*
        For every movement check if we are on a valid cell and it is not visited previously, then add the direction to current 
        path and call recursion to move to the next cell, after coming back from that recursive call, backtrack to the previous
        state of the data structures.
    */
    // 1. Move Up
    x--;
    if (isValidCell(x, y, n, m, isVisited)) {
        path.push_back('U');
        isVisited[x][y] = 1;
        findPathHelper(m, n, paths, isVisited, x, y, path);        
        isVisited[x][y] = 0;
        path.pop_back();
    }
    x++;
    
    // 2. Move Right
    y++;
    if (isValidCell(x, y, n, m, isVisited)) {
        path.push_back('R');
        isVisited[x][y] = 1;
        findPathHelper(m, n, paths, isVisited, x, y, path);        
        isVisited[x][y] = 0;
        path.pop_back();
    }
    y--;
    
    // 3. Move Down
    x++;
    if (isValidCell(x, y, n, m, isVisited)) {
        path.push_back('D');
        isVisited[x][y] = 1;
        findPathHelper(m, n, paths, isVisited, x, y, path);        
        isVisited[x][y] = 0;
        path.pop_back();
    }
    x--;
    
    // 4. Move Left
    y--;
    if (isValidCell(x, y, n, m, isVisited)) {
        path.push_back('L');
        isVisited[x][y] = 1;    
        findPathHelper(m, n, paths, isVisited, x, y, path);        
        isVisited[x][y] = 0;
        path.pop_back();
    }
    y++;
    
    return ;
}

vector<string> findPath(vector<vector<int>> &m, int n) {
    // Store all paths in vector
    vector<string> paths;
    // Keep track of visited cells here
    vector<vector<bool>> isVisited(n, vector<bool>(n, 0));
    // Use 2 indexes to keep track of x and y index of rat position
    int x = 0;
    int y = 0;
    // Keep track of current path
    string path;
    
    // Handle case where rat is stuck on source node
    if (m[x][y] == 1) {
        isVisited[x][y] = 1;
        findPathHelper(m, n, paths, isVisited, x, y, path);
    }
    
    return paths;    
}


// 3.


// 4.


// 5.


int main() {

    vector<vector<int>> m{
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };

    vector<string> allPaths = findPath(m, m.size());
    for (auto path: allPaths) cout << path << " ";
    cout << endl;

    return 0;
}