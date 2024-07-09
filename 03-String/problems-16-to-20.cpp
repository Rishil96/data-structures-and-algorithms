#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

// 16. String to Integer (atoi)
int myAtoi(string s) {
    // Store integer in string initially
    int ans = 0;
    int index = 0;      // Use this to go through the string
    bool isPositive = true;

    // 1. Skip leading whitespaces
    while (index < s.size() && s[index] == ' ') index++;

    // 2. Check if integer is +ve or -ve
    if (s[index] == '+' || s[index] == '-') {
        if (s[index] == '-') isPositive = false;
        index++;
    }

    // 3a. Skip leading zeros
    while (index < s.size() && s[index] == '0') index++;

    // 3b. Read integer
    while (index < s.size() && (s[index] >= '0' && s[index] <= '9')) {
        int digit = s[index++] - '0';
        // 4. Round up integer to fit 32-bit signed integer range
        // Point of error: Handle 32-bit integer range
        if (ans > 214748364 || (ans == 214748364 && digit > 7)) return isPositive ? INT_MAX : INT_MIN;
        else {
            ans = ans * 10 + digit;
        }
    }

    return isPositive ? ans : -ans;
}


// 17. String Compression
int compress(vector<char>& chars) {
    char currChar = chars[0];       // Stores curr character of which we are counting frequency
    int writer = 0;                 // Used to write character and its frequency as compression
    int reader = 0;                 // Used to loop through array and get count of characters
    int count = 0;                  // Keep frequency of current character


    while (reader < chars.size()) {
        // Read till we can compress currChar and increase count
        if (chars[reader] == currChar) {
            reader++;
            count++;
        }
        // Process for new character
        else {
            // First write the current character in array
            chars[writer++] = currChar;
            // Save index just after curr character to reverse the count
            int start = writer;
            // Write count using writer index if its greater than 1
            if (count > 1) {
                while (count) {
                    char digit = (count % 10) + '0';
                    count /= 10;
                    chars[writer++] = digit;
                }
                // Reverse the frequency count as when > 10 it will be written in reverse
                reverse(chars.begin() + start, chars.begin() + writer);
            }
            // Update current character to the new one and reset count to 0
            currChar = chars[reader];
            count = 0;
        }
    }

    // Process the last character the same way as done in loop as loop won't handle last character
    chars[writer++] = currChar;
    int start = writer;
    if (count > 1) {
        while (count) {
            char digit = (count % 10) + '0';
            count /= 10;
            chars[writer++] = digit;
        }
        reverse(chars.begin() + start, chars.begin() + writer);
    }

    return writer;
}


// 18. Integer to Roman
string intToRoman(int num) {
    string roman;       // Store roman in variable

    // Convert num to roman using symbol table
    while (num) {
        if (num >= 1000) {
            roman.push_back('M');
            num -= 1000;
        }
        else if (num >= 900) {
            roman.append("CM");
            num -= 900;
        }
        else if (num >= 500) {
            roman.push_back('D');
            num -= 500;
        }
        else if (num >= 400) {
            roman.append("CD");
            num -= 400;
        }
        else if (num >= 100) {
            roman.push_back('C');
            num -= 100;
        }
        else if (num >= 90) {
            roman.append("XC");
            num -= 90;
        }
        else if (num >= 50) {
            roman.push_back('L');
            num -= 50;
        }
        else if (num >= 40) {
            roman.append("XL");
            num -= 40;
        }
        else if (num >= 10) {
            roman.push_back('X');
            num -= 10;
        }
        else if (num >= 9) {
            roman.append("IX");
            num -= 9;
        }
        else if (num >= 5) {
            roman.push_back('V');
            num -= 5;
        }
        else if (num >= 4) {
            roman.append("IV");
            num -= 4;
        }
        else {
            roman.push_back('I');
            num--;
        }
    }

    return roman;
}


// 19. ZigZag Conversion of String
string convert(string s, int numRows) {
    // Base Case
    if (numRows == 1) return s;

    // Create map to hold characters as per row
    map<int, vector<char>> rows;

    // Keep track of rows and direction of zigzag
    int rowIndex = 0;
    bool dir = true;
    
    // Process zigzag
    for (int i=0; i<s.size(); i++) {
        if (dir) {
            rows[++rowIndex].push_back(s[i]);
            if (rowIndex == numRows) dir = false;
        }
        else {
            rows[--rowIndex].push_back(s[i]);
            if (rowIndex == 1) dir = true;
        }
    }

    // Build output string using the rows map
    string output;
    for (auto it: rows) {
        for (auto ch: rows[it.first]) {
            output.push_back(ch);
        }
    }

    return output;
}


// 20. Largest Number
static bool cmp(string a, string b) {
    if (a.size() == b.size()) return a > b;
    else return (a + b) > (b + a);
}

string largestNumber(vector<int>& nums) {
    // Convert integers to string and store it in array
    vector<string> strNums;
    for (auto n: nums) strNums.push_back(to_string(n));

    // Sort the array as per largest number logic using custom comparator
    sort (strNums.begin(), strNums.end(), cmp);

    // Build answer by appending the strings from largest to smallest
    string output;
    for (auto n: strNums) {
        // Handle initial zeros
        if (output.empty() && n == "0") continue;
        output.append((n));
    }

    // Set answer to 0 incase of empty output
    if (output.empty()) output += '0';
    return output;
}




int main() {

    

    return 0;
}