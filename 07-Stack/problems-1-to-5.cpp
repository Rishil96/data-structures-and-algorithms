#include <iostream>
#include <stack>
#include <vector>
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


// 4. Remove Redundant Parentheses
string removeRedundantParentheses(string expression) {
    vector<bool> valid(expression.size(), 1);
    stack<pair<char, int>> chars;
    
    for (int i=0; i<expression.size(); i++) {
        char ch = expression[i];
        // Add opening bracket and its index in stack
        if (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            chars.push({ch, i});
        }
        // If operator found between closing bracket, it is valid bracket else it is invalid bracket
        else if (ch == ')') {
            // Pop from stack till we get corresponding opening bracket and mark true if any operator found
            bool operatorFound = false;
            while (!chars.empty() && chars.top().first != '(') {
                operatorFound = true;
                chars.pop();
            }
            // If operator not found then mark both opening and closing brackets as invalid
            if (!operatorFound) {
                valid[chars.top().second] = false;
                valid[i] = false;
            }
            // Pop opening bracket from stack
            chars.pop();
        }
    }

    // Build answer using expression input and valid bool array
    string ans;
    for (int i=0; i<expression.size(); i++) {
        if (valid[i]) ans.push_back(expression[i]);
    }

    return ans;
}


// 5. MinStack
class MinStack {
public:
    vector<pair<int, int>> st;
    MinStack() {
        
    }
    
    void push(int val) {
        if (st.empty()) st.push_back({val, val});
        else st.push_back({val, min(val, st.back().second)});
    }
    
    void pop() {
        st.pop_back();
    }
    
    int top() {
        return st.back().first;
    }
    
    int getMin() {
        return st.back().second;
    }
};



int main() {

    cout << "Remove Redundant Parentheses 1: " << removeRedundantParentheses("(A*(B+C))") << endl;
    cout << "Remove Redundant Parentheses 2: " << removeRedundantParentheses("A+(B+(C))") << endl;
    cout << "Remove Redundant Parentheses 3: " << removeRedundantParentheses("((A+B))+((C+D)+E)-((F*G))") << endl;

    return 0;
}