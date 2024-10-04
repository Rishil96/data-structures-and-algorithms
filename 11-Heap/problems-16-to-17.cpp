#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// 16. Minimum difference in sums after removal of elements
long long minimumDifference(vector<int>& nums) {
    
    /* Step 1: Declare variables and data structures required for solving the problem */
    // n => number of elements to remove
    long long n = nums.size() / 3;

    // Array to store minimum sum of n elements from left to right
    vector<long long> minSumArray(nums.size(), -1);
    // Array to store maximum sum of n elements from right to left
    vector<long long> maxSumArray(nums.size(), -1);

    // Use maxHeap to store minimum elements from left to right and remove max elements to reduce difference
    priority_queue<long long> maxHeap;
    // Use minHeap to store maximum elements from right to left and remove min elements to reduce difference
    priority_queue<long long, vector<long long>, greater<long long>> minHeap;

    /* Step 2: Process minimum sum from left to right */
    // Keep track of sum
    long long currSum = 0;
    
    // Build min sum array
    for (long long i=0; i<nums.size(); i++) {
        // If we have not used n elements yet, add current element to max heap and update current sum
        if (maxHeap.size() < n) {
            currSum += nums[i];
            maxHeap.push(nums[i]);
            // If n elements are used then update minimum sum array
            if (maxHeap.size() == n) minSumArray[i] = currSum;
        }
        /* Here, maxHeap already has n elements, so for every new element check if maxHeap's top 
        is greater than current element, if so then remove max element and add current element */ 
        else {
            // There is a larger element in max heap than current element
            if (maxHeap.top() > nums[i]) {
                currSum -= maxHeap.top();
                maxHeap.pop();
                currSum += nums[i];
                maxHeap.push(nums[i]);
            }
            // Update min sum of n elements at current point 
            minSumArray[i] = currSum;
        }
    }

    /* Step 3: Process maximum sum from right to left */
    currSum = 0;

    // Build max sum array
    for (long long i=nums.size()-1; i>=0; i--) {
        // Directly add current elements in array and current sum till n elements are not used
        if (minHeap.size() < n) {
            currSum += nums[i];
            minHeap.push(nums[i]);
            // Update current sum when n elements are used
            if (minHeap.size() == n) maxSumArray[i] = currSum;
        }
        // Here minHeap has n elements so process every element from here
        else {
            // If current element is larger than top of minHeap, add it to minHeap and remove smaller top
            if (minHeap.top() < nums[i]) {
                currSum -= minHeap.top();
                minHeap.pop();
                currSum += nums[i];
                minHeap.push(nums[i]);
            }
            maxSumArray[i] = currSum;
        }
    }

    long long minSum = INT64_MAX;

    /* Step 4: Find the minimum sum difference by using p as a partition to the array*/
    for (long long p=0; p<nums.size()-1; p++) {
        // Continue if we don't have a minSum or maxSum
        if (minSumArray[p] == -1 || maxSumArray[p+1] == -1) continue;
        long long currSumDiff = minSumArray[p] - maxSumArray[p+1];
        minSum = min(minSum, currSumDiff);
    }

    return minSum;
}


// 17. Minimum number of refuelling stops



int main() {

    

    return 0;
}