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


// 2. 


// 3.


// 4.


// 5.



int main() {

    

    return 0;
}