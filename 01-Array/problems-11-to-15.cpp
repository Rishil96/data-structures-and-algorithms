#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// 11. Index of First repeating element in an array
int firstRepeated(int arr[], int n) {
    // Use variable to store repeating number and its index
    int repeatingIndex = -1;
    int repeatingNum = -1;
    // Store first repeating index of a given number 
    map<int, int> mp;
    
    // Loop through the array
    for (int i=0; i<n; i++) {
        // If number is not repeated yet, add the number and its index to the map
        if (mp.find(arr[i]) == mp.end()) {
            mp[arr[i]] = i;
        }
        // Else number is repeated, if we have not received any repeating number or the previous repeating number's index is greater than
        // current number, store the current repeating number and its index 
        else {
            if (repeatingNum == -1 || repeatingIndex > mp[arr[i]]) {
                repeatingIndex = mp[arr[i]];
                repeatingNum = arr[i];
            }
        }
    }
    
    return repeatingIndex == -1 ? repeatingIndex : repeatingIndex + 1;
}


// 12. Common elements in 3 sorted arrays 
vector <int> commonElements (int A[], int B[], int C[], int n1, int n2, int n3) { 
    // Store ans in vector
    vector<int> ans;
    
    // Use 3 indexes to traverse all 3 arrays
    int a = 0;
    int b = 0;
    int c = 0;
    
    // Traverse all 3 arrays
    while (a < n1 && b < n2 && c < n3) {
        // If all 3 elements are same and it is not duplicate, add it in ans array and move all pointers ahead by 1
        if (A[a] == B[b] && B[b] == C[c]) {
            if (ans.size() > 0 && ans.back() != A[a] || ans.size() == 0) ans.push_back(A[a]);
            a++;
            b++;
            c++;
        }
        // If element at a is smaller than element at b increment a
        else if (A[a] < B[b]) {
            a++;
        }
        // If element at b is smaller than element at c increment b
        else if (B[b] < C[c]) {
            b++;
        }
        // Else increment c
        else c++;
    }
    
    return ans;
}


// 13. Wave Print a 2d array
void wavePrint(vector<vector<int>> arr) {
    
    bool dir = true;

    // Traverse the array in wave pattern
    for (int col=0; col<arr[0].size(); col++) {
        // Traverse top to down if dir is true
        if (dir) {
            for (int row=0; row<arr.size(); row++) cout << arr[row][col] << " ";
            dir = !dir;
        }
        // Traverse bottom to top if dir is false
        else {
            for (int row=arr.size()-1; row>=0; row--) cout << arr[row][col] << " ";
            dir = !dir;
        }
    }
    
}


// 14. Spiral Print a 2D array
vector<int> spiralOrder(vector<vector<int>>& matrix) {

    // Store answer in vector
    vector<int> ans;

    // Set boundaries of row and column that will reduce once we keep traversing the edges in spiral form
    int rowStart = 0;
    int rowEnd = matrix.size() - 1;
    int colStart = 0;
    int colEnd = matrix[0].size() - 1;

    // Set indexes to use to traverse
    int currRow = 0;
    int currCol = 0;

    // Use n as total number of elements and reduce it everytime we traverse an element, use n as breaking point of traversal
    int n = matrix.size() * matrix[0].size();

    // Spiral Order
    while (n > 0) {
        // Traverse from Top left to Top right
        for ( ; currCol <= colEnd ; currCol++) {
            ans.push_back(matrix[currRow][currCol]);
            n--;
        }
        currCol--;
        rowStart++;
        currRow++;

        // Traverse from Top right to Bottom right
        for ( ; currRow <= rowEnd ; currRow++) {
            ans.push_back(matrix[currRow][currCol]);
            n--;
        }
        currRow--;
        colEnd--;
        currCol--;

        if (n <= 0) break;

        // Traverse from Bottom right to Bottom left
        for ( ; currCol >= colStart ; currCol--) {
            ans.push_back(matrix[currRow][currCol]);
            n--;
        }
        currCol++;
        rowEnd--;
        currRow--;

        // Traverse from Bottom left to Top left
        for ( ; currRow >= rowStart ; currRow--) {
            ans.push_back(matrix[currRow][currCol]);
            n--;
        }
        currRow++;
        colStart++;
        currCol++;
    }

    return ans;
}


// 15. Factorial of a large number
vector<int> factorial(int N){
    // Create answer array to store digits of ans and add 1 in it, where 1 is the first number to multiply in factorial range
    vector<int> fact;
    fact.push_back(1);
    int carry = 0;
    
    // Loop from 2 to N to multiply each number in the array
    for (int num=2; num<=N; num++) {
        // Multiply num to every digit of curr answer, store the new digit after multiplication on the same index and update carry
        for (int i=0; i<fact.size(); i++) {
            int currDigit = fact[i];                // Current digit to multiply
            int ans = num * currDigit + carry;      // Ans of num and current digit product
            int ansDigit = ans % 10;                // Get ans digit to add in current index
            carry = ans / 10;                       // Update carry to later on add remaining digits
            fact[i] = ansDigit;                     // Update ans vector with new digit at current index
        }
        // Add carry digits to the end of array
        while (carry) {
            fact.push_back(carry % 10);
            carry /= 10;
        }
    }
    
    // Add carry digits to the end of array
    while (carry) {
        fact.push_back(carry % 10);
        carry /= 10;
    }
    
    reverse(fact.begin(), fact.end());
    return fact;
}


int main() {

    vector<vector<int>> arr {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };

    cout << "Wave Print: ";
    wavePrint(arr);

    return 0;
}