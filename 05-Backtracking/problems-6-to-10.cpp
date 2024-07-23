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


// 7. Count Inversions
long long int merge(long long arr[], vector<long long>& temp, int start, int mid, int end) {
    // i => traverse left subarray
    // j => traverse right subarray
    // k => index to write smaller elements first in temp
    // c => store count of inversions
    int i=start, j=mid+1, k=start;
    long long int c = 0;
    
    // Loop till i and j are valid indexes in respective subarrays
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            // If inversion/swap is needed, make the swap and store count
            temp[k++] = arr[j++];
            /*
            In this case, right element was smaller than left element 
            means it will come before all the remaining elements on left subarray
            so if there are 3 more elements remaining to be placed from left
            subarray then 3 swaps have to be done for current right element
            to be placed at its correct position and that calculation can be
            done by (mid - i + 1)
            */
            c += mid - i + 1;
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= end) {
        temp[k++] = arr[j++];
    }
    
    while (start <= end) {
        arr[start] = temp[start];
        ++start;
    }
    
    return c;
}

long long int mergeSort(long long arr[], vector<long long>& temp, long long start, long long end) {
    // Base Case
    if (start >= end) return 0;
    
    long long mid = start + (end - start) / 2;
    long long int c = 0;
    
    // Call merge sort for left and right subarray and merge function
    c += mergeSort(arr, temp, start, mid);
    c += mergeSort(arr, temp, mid+1, end);
    
    c +=merge(arr, temp, start, mid, end);
    
    // Return the sum of both merge sort and merge function calls
    return c;
}

long long int inversionCount(long long arr[], int n) {
    long long int count;                        // Store total inversion count
    vector<long long> temp(n, 0);               // Temporary array for merge sort
    count = mergeSort(arr, temp, 0, n-1);       // Recursive call

    return count;
}


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


// 9. Maximum Subarray Sum
int getSum(vector<int>& nums, int start, int end) {
    // Base Case: If subarray is a single element return it
    if (start == end) return nums[start];

    // Ek Case
    int mid = start + (end - start) / 2;

    // Get maximum subarray sum from left and right
    int maxLeftSubArraySum = getSum(nums, start, mid);
    int maxRightSubArraySum = getSum(nums, mid+1, end);

    // Calculate cross border sum i.e. from middle
    int leftBorderSum = 0;
    int rightBorderSum = 0;
    int maxLeftBorderSum = INT_MIN;
    int maxRightBorderSum = INT_MIN;
    
    // Loop to get max sum from left side of middle subarray
    for (int i=mid; i>=start; i--) {
        leftBorderSum += nums[i];
        maxLeftBorderSum = max(leftBorderSum, maxLeftBorderSum);
    }

    // Loop to get max sum from right side of middle subarray
    for (int i=mid+1; i<=end; i++) {
        rightBorderSum += nums[i];
        maxRightBorderSum = max(rightBorderSum, maxRightBorderSum);
    }

    return max(maxLeftBorderSum + maxRightBorderSum, max(maxLeftSubArraySum, maxRightSubArraySum));
}

int maxSubArray(vector<int>& nums) {
    return getSum(nums, 0, nums.size()-1);
}


// 10. Quick Sort with end element as pivot
void quickSort(int a[], int start, int end) {
    // Base Case
    if (start >= end) return ;

    // Ek Case
    // Partition Logic
    int pivot = end;
    int i = start - 1;
    int j = start;

    // Use i and j to traverse the array such that if j element is less than pivot element then place it on i after incrementing i.
    while (j < pivot) {
        if (a[j] < a[pivot]) {
            ++i;
            swap(a[i], a[j]);
        }
        j++;
    }
    i++;
    swap(a[i], a[pivot]);
    pivot = i;

    // Call quick sort for left and right subarrays from pivot
    quickSort(a, start, pivot - 1);
    quickSort(a, pivot+1, end);
}



int main() {

    

    return 0;
}