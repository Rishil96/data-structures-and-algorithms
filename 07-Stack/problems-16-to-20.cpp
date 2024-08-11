#include <iostream>
#include <stack>
#include <vector>
using namespace std;


// 16. Maximal Rectangle
vector<int> getPSI(vector<int>& hist) {
    vector<int> ans(hist.size(), -1);
    stack<int> st;

    for (int i=0; i<hist.size(); i++) {
        // Remove all indexes for which elements are greater than equal to current element
        while (!st.empty() && hist[i] <= hist[st.top()]) {
            st.pop();
        }

        // Update current answer
        if (st.empty()) ans[i] = -1;
        else ans[i] = st.top();

        // Add current index
        st.push(i);
    }

    return ans;
}

vector<int> getNSI(vector<int>& hist) {
    vector<int> ans(hist.size(), hist.size());
    stack<int> st;

    for (int i=hist.size()-1; i>=0; i--) {
        // Remove all indexes for which elements are greater than equal to current element
        while (!st.empty() && hist[i] <= hist[st.top()]) {
            st.pop();
        }

        // Update current answer
        if (st.empty()) ans[i] = hist.size();
        else ans[i] = st.top();

        // Add current index
        st.push(i);
    }

    return ans;
}

int maxRectHelper(vector<int>& hist) {
    // Get previous and next smallest index
    vector<int> psi = getPSI(hist);
    vector<int> nsi = getNSI(hist);

    int maxRect = INT_MIN;

    // Calculate area for each height of hist
    for (int i=0; i<hist.size(); i++) {
        int currRect = hist[i] * (nsi[i] - psi[i] - 1);
        maxRect = max(maxRect, currRect);
    }

    return maxRect;
}

int maximalRectangle(vector<vector<char>>& matrix) {
    // Logic to build histogram for every row
    vector<int> hist(matrix[0].size(), 0);
    
    int largestRect = INT_MIN;

    // Loop and build histogram
    for (int row=0; row<matrix.size(); row++) {
        for (int col=0; col<matrix[0].size(); col++) {
            // Use first row of matrix as it is
            if (row == 0) {
                hist[col] = matrix[row][col] - '0';
            }
            // Add height to hist if new base is 1 else set it to 0
            else {
                hist[col] = (matrix[row][col] == '0') ? 0 : 1 + hist[col];
            }
        }

        int currLargestRect = maxRectHelper(hist);
        largestRect = max(currLargestRect, largestRect);
    }

    return largestRect;
}


// 17. 


// 18.


// 19. Asteroid Collision
vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> col;

    for (int i=0; i<asteroids.size(); i++) {
        int currAst = asteroids[i];
        // No collision case
        if (col.empty() || (                        // Empty stack means no asteroid yet
            (col.top() < 0 && currAst < 0) ||        // Both left and right asteroid moving left
            (col.top() > 0 && currAst > 0) ||        // Both left and right asteroid moving right
            (col.top() < 0 && currAst > 0) )         // Left moving left and right moving right 
            ) {
            col.push(currAst);
        }
        // Collision Case
        else {
            col.push(currAst);                          // Add current asteroid in col stack
            while (col.size() > 1) {
                int rightAst = col.top(); col.pop();
                int leftAst = col.top(); col.pop();

                // If both asteroids are moving in same direction, push them back and break
                if ((leftAst < 0 && rightAst < 0) || (leftAst > 0 && rightAst > 0)) {
                    col.push(leftAst);
                    col.push(rightAst);
                }

                // Collision Case
                if (leftAst > 0 && rightAst < 0) {
                    // Left asteroid is bigger
                    if (abs(leftAst) > abs(rightAst)) {
                        col.push(leftAst);
                        break;
                    }
                    // Right asteroid is bigger
                    else if (abs(leftAst) < abs(rightAst)) {
                        col.push(rightAst);
                    }
                    // Both asteroids are of same size
                    else {
                        break;
                    }
                }
                // No collision Case
                else break;
            }
        }
    }
        
    // Build answer
    vector<int> ans(col.size(), 0);
    for (int i=ans.size()-1; i>=0; i--) {
        ans[i] = col.top(); col.pop();
    }

    return ans;
}


// 20. Daily Temperatures
vector<int> dailyTemperatures(vector<int>& temperatures) {
    /* 
    Use next larger element/index logic
    */
    // Answer array
    vector<int> waiting(temperatures.size(), 0);
    stack<int> st;

    for (int i=temperatures.size()-1; i>=0; i--) {
        // Remove all temperatures that are lesser than current temperature
        while (!st.empty() && temperatures[i] >= temperatures[st.top()]) st.pop();
        
        // Write current answer
        if (st.empty()) waiting[i] = 0;
        else waiting[i] = st.top() - i;

        // Push current day
        st.push(i);
    }
    
    return waiting;
}



int main() {

    

    return 0;
}