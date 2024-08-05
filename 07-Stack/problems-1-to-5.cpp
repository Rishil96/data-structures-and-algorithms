#include <iostream>
#include <stack>
using namespace std;

// 1. Reverse a stack
void insertAtBottom(stack<int>& st, int topElement) {
    // Base Case
    if (st.empty()) {
        st.push(topElement);
        return ;
    }
    
    // Ek Case
    int top = st.top(); st.pop();
    insertAtBottom(st, topElement);
    st.push(top);
    
    return ;
}

void Reverse(stack<int> &St){
    // Base Case
    if (St.empty()) return ;
    
    // Ek Case
    // Store top element
    int topElement = St.top(); St.pop();
    Reverse(St);
    insertAtBottom(St, topElement);
    
    return ;
}


// 2. Valid Parentheses
bool isValid(string s) {
    stack<char> par;
    for (auto ch: s) {
        // Opening Bracket Case: Add in stack
        if (ch == '(' || ch == '[' || ch == '{') {
            par.push(ch);
        }
        // Closing Bracket Case: Pop fro stack if brackets match else return false
        else {
            if (par.empty()) return false;
            else if (ch == ')' && par.top() == '(') par.pop();
            else if (ch == ']' && par.top() == '[') par.pop();
            else if (ch == '}' && par.top() == '{') par.pop();
            else return false;
        }
    }

    // If stack is empty return true
    return par.empty();
}


// 3. Sort a stack
void insertSorted(stack<int> &s, int &element) {
    // Base Case: If stack becomes empty, single element is sorted so add the element and return
    if (s.empty()) {
        s.push(element);
        return ;
    }

    // Ek Case
    int topElement = s.top();

    // Place our element if it is greater than the top element
    if (element > topElement) {
        s.push(element);
        return ;
    }
    // Else call recursion to find the correct location for our element
    else {
        s.pop();
        insertSorted(s, element);
        s.push(topElement);
    }

    return ;
}

void sortStack(stack<int> &s) {
    // Base Case
    if (s.empty()) return ;

    // Ek Case
    int element = s.top();  s.pop();
    sortStack(s);

    // Baaki Recursion 
    insertSorted(s, element);
    return ;
}


// 4.


// 5.



int main() {

    

    return 0;
}