#include <iostream>
#include <vector>
using namespace std;

// 11. Print all subarrays using Recursion
void print(vector<int> arr, int start, int end) {
    // Base Case
    if (end >= arr.size()) return;

    // One Case
    // Print subarray for current start and end
    for (int i=start; i<=end; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Increase end by one to get the next subarray from current start
    print(arr, start, end+1);
}

void printSub(vector<int> arr) {
    // Use this loop to give a start and end point for each subarray
    for (int i=0; i<arr.size(); i++) {
        print(arr, i, i);
    }
}
 

// 12. Buy and Sell Stocks
void maxProfitHelper(vector<int>& prices, int i, int &buyPrice, int &profit) {
    // Base Case
    if (i >= prices.size()) return ;

    // Ek Case
    buyPrice = min(buyPrice, prices[i]);        // Update buy price to the lowest price
    int currProfit = prices[i] - buyPrice;      // Calculate current profit
    profit = max(profit, currProfit);           // Update maximum profit

    // Baki Recursion
    maxProfitHelper(prices, i+1, buyPrice, profit);
}

int maxProfit(vector<int>& prices) {
    int buyPrice = INT_MAX;
    int profit = INT_MIN;
    maxProfitHelper(prices, 0, buyPrice, profit);
    return profit;
}


// 13. Integer to English Words
string convertNumber(int num, vector<pair<int, string>> &numStrings) {
    // Base Case
    if (num == 0) return "Zero";

    // Ek Case
    for (auto numberItem: numStrings) {
        int currNum = numberItem.first;
        string currString = numberItem.second;

        // If number in map is greater than our input, continue to next as we can't divide our number
        if (currNum > num) continue;

        // Process number

        /* 
        Left part: Left part is only applicable when the input number is >= 100
        E.g. 1. 89 won't have left part, just middle = "Eighty" and right = "Nine"
        E.g. 2. 102 will have all three parts, left = "One", middle = "Hundred", right = "Two" 
        */
        string left;
        if (num >= 100)
            left = convertNumber(num / currNum, numStrings) + " ";
        
        // Middle part: will be the number from our mapper
        string middle = currString;

        /* 
        Right part: will only be appicable when we have a remainder from the division of input and 
        map number.
        E.g. 1. 81 => Here middle is 80 so dividing 81 / 80 will result in remainder 1, 
        so right part will exist
        E.g. 2. 70 => Here middle is 70 so dividing 70 / 70 will result in remainder 0, 
        so right part will not exist
        */
        string right;
        if (num % currNum > 0)
            right = " " + convertNumber(num % currNum, numStrings);

        return left + middle + right;
    }

    return "Zero";
}

string numberToWords(int num) {
    // Vector Map for String representations of Numbers
    vector<pair<int, string>> numStrings {
        {1000000000, "Billion"}, {1000000, "Million"}, {1000, "Thousand"}, {100, "Hundred"}, 
        {90, "Ninety"}, {80, "Eighty"}, {70, "Seventy"}, {60, "Sixty"}, {50, "Fifty"}, {40, "Forty"},
        {30, "Thirty"}, {20, "Twenty"}, {19, "Nineteen"}, {18, "Eighteen"}, {17, "Seventeen"},
        {16, "Sixteen"}, {15, "Fifteen"}, {14, "Fourteen"}, {13, "Thirteen"}, {12, "Twelve"}, 
        {11, "Eleven"}, {10, "Ten"}, {9, "Nine"}, {8, "Eight"}, {7, "Seven"}, {6, "Six"}, {5, "Five"},
        {4, "Four"}, {3, "Three"}, {2, "Two"}, {1, "One"}
    };

    return convertNumber(num, numStrings);
}


// 14. WildCard Matching
bool wildMatch(string &s, string &p, int sPtr, int pPtr) {
    // Base Case 1: Both string and part is consumed
    if (sPtr >= s.size() && pPtr >= p.size()) return true;

    // Base Case 2: Pattern is consumed but not string
    if (pPtr >= p.size()) return false;

    // Base Case 3: String is consumed but not pattern
    if (sPtr >= s.size()) {
        // Consume * from pattern by matching no characters
        while (pPtr < p.size() && p[pPtr] == '*') pPtr++;
        return pPtr >= p.size();
    }

    // Ek Case
    // Case 1: Direct match
    if (s[sPtr] == p[pPtr] || p[pPtr] == '?') return wildMatch(s, p, sPtr+1, pPtr+1);
    // Case 2: * match
    else if (p[pPtr] == '*') {
        // Include Exclude pattern : Consume 1 character and don't consume character
        return wildMatch(s, p, sPtr+1, pPtr) || wildMatch(s, p, sPtr, pPtr+1);
    }
    // Case 3: No match
    return false;
}

bool isMatch(string s, string p) {
    return wildMatch(s, p, 0, 0);
}


// 15. Perfect Squares
int perfectSquares(int n) {
    // Base Case
    if (n == 0) return 0;           // We consumed n with perfect squares
    if (n < 0) return INT_MAX;      // If n goes below zero it means invalid answer

    // Ek Case
    int minAns = INT_MAX;

    for (int num=1; num<=sqrt(n); num++) {
        // Calculate answer by subtracting with square of current number
        int currAns = perfectSquares(n - (num * num));
        // If current answer is a valid one, update in answer variable
        if (currAns != INT_MAX) minAns = min(minAns, 1 + currAns);
    }

    return minAns;
}

int numSquares(int n) {
    return perfectSquares(n);
}


int main() {

    printSub(vector<int>{1, 2, 3, 4, 5});

    return 0;
}