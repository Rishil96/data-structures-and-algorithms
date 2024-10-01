#include <iostream>
#include <queue>
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


// 14.


// 15.



int main() {

    

    return 0;
}