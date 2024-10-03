#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 11. Find Median from the data stream
class MedianFinder {
public:
    
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    MedianFinder() {
        
    }
    
    void addNum(int num) {
        // Both max and min heap have equal number of elements or min heap has more elements
        if (maxHeap.size() <= minHeap.size()) {
            maxHeap.push(num);
        }
        // Max heap has more elements
        else if (minHeap.size() < maxHeap.size()) {
            minHeap.push(num);
        }

        // Rearrange elements        
        if (!minHeap.empty() && !maxHeap.empty() && maxHeap.top() > minHeap.top()) {
            int maxTop = maxHeap.top(); maxHeap.pop();
            int minTop = minHeap.top(); minHeap.pop();
            maxHeap.push(minTop);
            minHeap.push(maxTop);
        }
    }
    
    double findMedian() {
        // Case where minHeap has more elements
        if (!minHeap.empty() && minHeap.size() > maxHeap.size()) return minHeap.top();
        // Case where maxHeap has more elements
        if (!maxHeap.empty() && maxHeap.size() > minHeap.size()) return maxHeap.top();
        // Case where both max and min heaps have same number of elements
        double maxTop = maxHeap.top();
        double minTop = minHeap.top();

        return (maxTop + minTop) / 2.0;
    }
};


// 12. Merge two binary max heaps
void heapify(vector<int>& heap, int &index, int &size) {
    // Get children indexes
    int leftChildIndex = index * 2 + 1;
    int rightChildIndex = leftChildIndex + 1;
    int largestIndex = index;
    
    // Compare which of the three indexes is greater
    if (leftChildIndex < size && heap[largestIndex] < heap[leftChildIndex]) 
        largestIndex = leftChildIndex;
    if (rightChildIndex < size && heap[largestIndex] < heap[rightChildIndex]) 
        largestIndex = rightChildIndex;

    // If largest is the same as index it means the current value is at correct position
    if (largestIndex == index) return ;
    else {
        swap(heap[index], heap[largestIndex]);
        heapify(heap, largestIndex, size);
    }
}

vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) {

    // Step 1: Merge both arrays
    for (int i=0; i<b.size(); i++) {
        a.push_back(b[i]);
    }

    // Step 2: Heapify the array from n/2 to 0
    n = a.size();
    for (int i=n/2; i>=0; i--) {
        heapify(a, i, n);
    }

    return a;
}


// 13. K closest points to origin
/* MinHeap approach */
class compare {
public:
    bool operator()(pair<double, int> a, pair<double, int> b) {
        return a.first > b.first;
    }
};

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    /*  
        MinHeap to store the points with their distances from origin from smallest to largest 
        (heapelement is distance from origin, index of point in main vector) 
    */
    priority_queue<pair<double, int>, vector<pair<double, int>>, compare> minHeap;
    vector<vector<int>> answer;

    double originX = 0;
    double originY = 0;

    for (int i=0; i<points.size(); i++) {
        // Current point distance
        double currX = points[i][0];
        double currY = points[i][1];

        // Calculate distance and push distance, index pair in min heap
        double distance = sqrt(pow(currX - originX, 2) + pow(currY - originY, 2));
        minHeap.push({distance, i});
    }

    // Pop out k smallest elements
    while (k--) {
        auto topElement = minHeap.top(); minHeap.pop();
        answer.push_back(points[topElement.second]);
    }

    return answer;
}

/* MaxHeap approach */
double getDistance(double &x, double &y) {
    // Origin co-ordinates
    double originX = 0;
    double originY = 0;

    return sqrt(pow(x - originX, 2) + pow(y - originY, 2));
}

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    /*  
    MaxHeap to hold k closest elements
    */
    priority_queue<pair<double, int>> maxHeap;
    vector<vector<int>> answer;

    // 1. Process first k elements
    for (int i=0; i<k; i++) {
        // Current point co-ordinates
        double currX = points[i][0];
        double currY = points[i][1];

        // Calculate distance and push distance, index pair in min heap
        double distance = getDistance(currX, currY);
        maxHeap.push({distance, i});
    }

    // 2. Process remaining array of points
    for (int i=k; i<points.size(); i++) {
        // Current point co-ordinates
        double currX = points[i][0];
        double currY = points[i][1];

        // Calculate distance
        double distance = getDistance(currX, currY);
        if (maxHeap.top().first > distance) {
            maxHeap.pop();
            maxHeap.push({distance, i});
        }
    }

    // 3. Build answer
    while (!maxHeap.empty()) {
        auto topElement = maxHeap.top(); maxHeap.pop();
        answer.push_back(points[topElement.second]);
    }

    return answer;
}


// 14. Sliding Window Maximum
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    // Use MaxHeap to keep track of maximum element in current window
    // {element, index}
    priority_queue<pair<int, int>> maxHeap;

    // 1. Process first k elements
    for (int i=0; i<k; i++) {
        maxHeap.push({nums[i], i});
    }

    vector<int> ans;

    // 2. Get answer for first window
    ans.push_back(maxHeap.top().first);

    // 3. Process remaining windows
    for (int i=k; i<nums.size(); i++) {
        // Remove elements that are out of range of current window
        while (!maxHeap.empty() && maxHeap.top().second <= i - k) maxHeap.pop();

        // Add current element in our window
        maxHeap.push({nums[i], i});

        // Update answer array for current window
        ans.push_back(maxHeap.top().first);
    }

    return ans;
}


// 15. Get biggest 3 rhombus
bool validRhombus(pair<int,int> &up, pair<int,int> &right, pair<int,int> &down, pair<int,int> &left, int &row, int &col) {
    // Check up
    if (up.first < 0 || up.first >= row || up.second < 0 || up.second >= col) return false;
    // Check right
    if (right.first < 0 || right.first >= row || right.second < 0 || right.second >= col) return false;
    // Check down
    if (down.first < 0 || down.first >= row || down.second < 0 || down.second >= col) return false;
    // Check left
    if (left.first < 0 || left.first >= row || left.second < 0 || left.second >= col) return false;

    return true;
}

void expandRhombus(vector<vector<int>>& grid, int currRow, int currCol, int &rowSize, int &colSize, priority_queue<int> &maxHeap) {
    // Create 4 vertices that represents four corner points of a rhombus
    pair<int, int> up = make_pair(currRow-1, currCol);          // Expands to the top
    pair<int, int> right = make_pair(currRow, currCol+1);       // Expands to the right
    pair<int, int> down = make_pair(currRow+1, currCol);        // Expands to the bottom
    pair<int, int> left = make_pair(currRow, currCol-1);        // Expands to the left

    while (validRhombus(up, right, down, left, rowSize, colSize)) {
        // Calculate Rhombus Sum
        // A : Add vertices
        int sum = grid[up.first][up.second] + grid[right.first][right.second] + grid[down.first][down.second] + grid[left.first][left.second];
        // B : Add edges
        int x, y;
        // Traverse UP to RIGHT
        x = up.first + 1;
        y = up.second + 1;

        while (x != right.first && y != right.second) {
            sum += grid[x++][y++];
        }

        // Traverse RIGHT to DOWN
        x = right.first + 1;
        y = right.second - 1;

        while (x != down.first && y != down.second) {
            sum += grid[x++][y--];
        }

        // Traverse DOWN to LEFT
        x = down.first - 1;
        y = down.second - 1;

        while (x != left.first && y != left.second) {
            sum += grid[x--][y--];
        }

        // Traverse LEFT to UP
        x = left.first - 1;
        y = left.second + 1;

        while (x != up.first && y != up.second) {
            sum += grid[x--][y++];
        }

        // Expand Rhombus
        up.first--;
        right.second++;
        down.first++;
        left.second--;

        // Add sum to heap
        maxHeap.push(sum);
    }
}

vector<int> getBiggestThree(vector<vector<int>>& grid) {
    // 1. Create a MaxHeap to hold rhombus sums
    priority_queue<int> maxHeap;

    // 2. Loop through the grid
    int row = grid.size(), col = grid[0].size();
    for (int r=0; r<grid.size(); r++) {
        for (int c=0; c<grid[r].size(); c++) {
            // 3. Consider the single cell as a rhombus and add it to heap as its sum
            maxHeap.push(grid[r][c]);
            // 4. Expand rhombus
            expandRhombus(grid, r, c, row, col, maxHeap);
        }
    }

    // 3. Add top 3 answers in array
    vector<int> ans;

    while (!maxHeap.empty() && ans.size() < 3) {
        int top = maxHeap.top();

        if (ans.size() > 0 && ans.back() == top) {
            maxHeap.pop();
        }
        else {
            ans.push_back(top);
            maxHeap.pop();
        }
    }

    return ans;
}


int main() {

    

    return 0;
}