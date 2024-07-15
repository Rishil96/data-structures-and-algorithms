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


// 3. N-Queens
bool canPlaceQueen(int &n, vector<string>& board, int row, int col) {
    /*
        Since we are placing queens from row 0 to n - 1, we always have to check we queens
        were placed in above rows such that a queen from current cell can capture it
        3 things to check :-
            1. is current column above current cell
            2. upper left diagonal
            3. upper right diagonal
    */
    
    // Check if queen exists in current column
    for (int r=0; r<row; r++) if (board[r][col] == 'Q') return false;

    // Check if queen exists in left upper diagonal
    int i = row;
    int j = col;

    while (i >= 0 && j >= 0) {
        if (board[i][j] == 'Q') return false;
        i--;
        j--;
    }
    
    // Check if queen exists in right upper diagonal
    i = row;
    j = col;

    while (i >= 0 && j < n) {
        if (board[i][j] == 'Q') return false;
        i--;
        j++;
    }

    return true;
}

void nQueenHelper(int &n, vector<vector<string>>& ans, vector<string>& board, int currRow) {
    /*
        In every helper call, we will try to place a queen in current row of the board
        If we are able to place a queen in current row, we call recursion to do the same
        for the next row, and if not we simple come back from that call
        If the Recursive call reaches the last row, it means N queens were placed successully
        so we save that instance of the board in our main answer variable
    */

    // Base Case: If currRow reached N, means all queens are placed, store answer
    if (currRow >= n) {
        ans.push_back(board);
        return ;
    }

    // Ek Case: Try to place queens in columns 1 to N - 1 of currRow
    for (int col=0; col<n; col++) {
        // If its possible to place queen on current cell, place it and call recursion for next row
        if (canPlaceQueen(n, board, currRow, col)) {
            board[currRow][col] = 'Q';
            nQueenHelper(n, ans, board, currRow + 1);
            board[currRow][col] = '.';          // Backtracking step
        }
    }

    return ;
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;                             // Answer storing vector
    vector<string> board(n);                                // Single board instance
    string singleRow;                                       // Single row instance with no queens
    for (int i=0; i<n; i++) singleRow.push_back('.');       // Build single row
    for (int row=0; row<n; row++) board[row] = singleRow;   // Add single rows in board

    // Use recursion to place N Queens in N rows of the empty board
    nQueenHelper(n, ans, board, 0);

    return ans;
}


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