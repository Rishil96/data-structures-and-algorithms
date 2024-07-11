#include <iostream>
using namespace std;

// 6. Reverse a string using Recursion
void reverseString(string& s, int l, int r) {
    // Base Case
    if (l >= r) return ;

    // Ek Case
    swap(s[l++], s[r--]);

    // Baaki Recursion
    return reverseString(s, l, r);
}


// 7. Add Strings
void add(string &num1, string& num2, int &i, int &j, string &ans, int &carry) {
    // Base Case
    if (i < 0 && j < 0) return ;

    // Ek Case
    int digit1 = i >= 0 ? num1[i--] - '0' : 0;
    int digit2 = j >= 0 ? num2[j--] - '0' : 0;

    int sum = digit1 + digit2 + carry;      // Add both digits
    int outputDigit = sum % 10;             // Get single digit to add in answer
    carry = sum / 10;                       // Update carry

    ans.push_back(outputDigit + '0');

    // Baaki Recursion Sambhaal Lega
    add(num1, num2, i, j, ans, carry);
}

string addStrings(string num1, string num2) {
    // Use 2 pointers to traverse both strings from right to left for addition
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    
    // Store ans and carry for each addition
    string ans;
    int carry = 0;

    add(num1, num2, i, j, ans, carry);

    // Add carry if left over
    if (carry) ans.push_back(carry + '0');

    // Reverse the answer
    reverse(ans.begin(), ans.end());
    
    return ans;
}


// 8. Maximum Sum of non-adjacent elements
int getMaxSum(int *arr, int &n, int index) {
    // Base Case
    if (index >= n) return 0;
    
    // Ek Case
    // Pick current element
    int pick = getMaxSum(arr, n, index + 2) + arr[index];
    // Don't pick current element
    int notPick = getMaxSum(arr, n, index + 1) + 0;
    
    return max(pick, notPick);
}

int findMaxSum(int *arr, int n) {
    // code here
    return getMaxSum(arr, n, 0);
}


// 9. Valid Palindrome using Recursion
bool isAlphaNum(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9');
}

bool checkPal(string &s, int &left, int &right) {
    // Base Case
    if (left >= right) return true;

    // Ek Case
    // Increment left in case of non-alphanumeric character
    if (!isAlphaNum(s[left])) {
        left++;
        return checkPal(s, left, right);
    }
    // Decrement right in case of non-alphanumeric character
    else if (!isAlphaNum(s[right])) {
        right--;
        return checkPal(s, left, right);
    }
    // Process for valid alphanumeric character
    else {
        char l = s[left] >= 'A' && s[left] <= 'Z' ? s[left] + 32 : s[left];
        char r = s[right] >= 'A' && s[right] <= 'Z' ? s[right] + 32 : s[right];

        if (l == r) {
            left++;
            right--;
            return checkPal(s, left, right);
        }

        return false;
    }
}

bool isPalindrome(string s) {
    // 2 pointers to compare from left and right ends
    int left = 0;
    int right = s.size() - 1;
    return checkPal(s, left, right);
}


// 10. Remove all occurrence of substring
string removeOccurrences(string &s, string &part) {
    // Check if substring exists
    auto found = s.find(part);

    // Base Case
    if (found == string :: npos) return s;

    // EK Case
    s.erase(found, part.size());

    // Baaki Recursion 
    return removeOccurrences(s, part);
}



int main() {

    string s = "And now the world shall feel pain... Almighty Push!";

    cout << "Reverse String: ";
    reverseString(s, 0, s.size()-1);
    cout << s << endl;   
    cout << "Reverse String: ";
    reverseString(s, 0, s.size()-1);
    cout << s << endl;   

    return 0;
}