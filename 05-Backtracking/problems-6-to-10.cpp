#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


// 6. Sudoku Solver
bool canPlaceNumber(vector<vector<char>>& board, int &row, int &col, char num) {
    // Check if number is present in current row
    for (int r=0; r<9; r++) {
        if (board[r][col] == num) return false;
    }
    // Check if number is present in current col
    for (int c=0; c<9; c++) {
        if (board[row][c] == num) return false;
    }
    // Check if number is present in current 3X3 grid
    int gridRow = 0;
    int gridCol = 0;

    // Get starting row of 3 X 3 grid
    if (row >= 3 && row < 6) gridRow = 3;
    if (row >= 6) gridRow = 6;

    // Get starting col of 3 X 3 grid
    if (col >= 3 && col < 6) gridCol = 3;
    if (col >= 6) gridCol = 6;

    // Check grid
    for (int r=gridRow; r<gridRow+3; r++) {
        for (int c=gridCol; c<gridCol+3; c++) {
            if (board[r][c] == num) return false;
        }
    }

    return true;
}

bool solve(vector<vector<char>>& board) {
    // Loop through all rows
    for (int row=0; row<9; row++) {
        // Loop through all columns
        for (int col=0; col<9; col++) {
            // Check if current cell (row, col) is empty
            if (board[row][col] == '.') {
                // Try to place all numbers from 1 to 9 in current cell
                for (char num='1'; num<='9'; num++) {
                    if (canPlaceNumber(board, row, col, num)) {
                        // Place current number
                        board[row][col] = num;
                        // Call recursion to place other empty cells
                        bool ans = solve(board);
                        // If a solution was found from recursion, return true
                        if (ans) return ans;
                        // If solution was not found, backtrack to previous state
                        else board[row][col] = '.';
                    }
                }
                // If no number from 1 - 9 could be placed, return false
                return false;
            }
            // If current cell is filled then continue to next cell
            else continue;
        }
    }
    // If for loops was continued due to no empty cells, code will reach here, return true
    return true;
}

void solveSudoku(vector<vector<char>>& board) {
    // Call recursion to solve sudoku
    solve(board);
}


// 7. 


// 8. In-place merge sort
void mergeInPlace(vector<int>& nums, int start, int mid, int end) {
    // Gap method: Keep swapping left and right elements if left > right and reduce gap once traversed fully
    int total_length = end - start + 1;                         // Length of current array
    int gap = (total_length / 2) + (total_length % 2);          // Gap variable to traverse the current array
    
    // Run while loop till gap is greater than 0
    while (gap > 0) {
        // Use 2 variables i an j with the gap as calculated above
        int i = start;
        int j = i + gap;

        // Traverse the current array using i and j and swap elements if element at i is greater than element at j
        while (j <= end) {
            if (nums[i] > nums[j]) swap(nums[i], nums[j]);
            i++; j++;
        }

        // Update gap to ceil of gap / 2
        gap = gap <= 1 ? 0 : (gap / 2) + (gap % 2);
    }

}

void mergeSort(vector<int> &nums, int start, int end) {
    // Base Case
    if (start >= end) return ;

    // Ek Case
    int mid = start + (end - start) / 2;

    // Left Call
    mergeSort(nums, start, mid);
    // Right Call
    mergeSort(nums, mid+1, end);

    // Merge Call
    mergeInPlace(nums, start, mid, end);
}


// 9.


// 10.


int main() {

    

    return 0;
}