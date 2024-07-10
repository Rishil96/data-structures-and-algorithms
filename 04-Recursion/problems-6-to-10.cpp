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


// 7.


// 8.


// 9.


// 10.



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