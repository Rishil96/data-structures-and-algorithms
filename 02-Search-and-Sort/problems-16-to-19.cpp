#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 16. Painter Partition Problem
bool canPaint(int arr[], int &n, int &k, long long &maxUnitsPerPainter) {
    long long allocatedPainters = 1;
    long long unitsPainted = 0;

    for (int i=0; i<n; i++) {
        int currBoardLength = arr[i];

        // If curr board length is greater than our limit return false
        if (currBoardLength > maxUnitsPerPainter) return false;

        // Check if current painter can paint the curr board while staying within our max units limit
        if (unitsPainted + currBoardLength <= maxUnitsPerPainter) {
            unitsPainted += currBoardLength;
        }
        // Assign the board to a new painter
        else {
            allocatedPainters++;
            unitsPainted = currBoardLength;
        }

        // If more painters are needed to complete this painting project, return false
        if (allocatedPainters > k) return false;
    }

    return true;
}

long long minTime(int arr[], int n, int k) {
    // Define search space to get answer
    long long left = 0;
    long long right = 0;

    for (int i=0; i<n; i++) right += arr[i];

    long long ans = -1;

    // Use Binary Search to figure out the number of units each painter must paint to minimize the time taken
    while (left <= right) {
        long long currUnitsPerPainter = left + (right - left) / 2;

        // If its possible to paint curr units by all painters, then store ans and try to minimize it
        if (canPaint(arr, n, k , currUnitsPerPainter)) {
            ans = currUnitsPerPainter;
            right = currUnitsPerPainter - 1;
        }
        // If not possible to paint curr units, increase the curr units
        else {
            left = currUnitsPerPainter + 1;
        }
    }

    return ans;
}


// 17. Aggressive Cows
bool canPlace(int &n, int &k, vector<int>& stalls, int &minDistance) {
    int lastPlacedIndex = 0;
    int placedCows = 1;

    // Loop through stalls and try to place cows
    for (int i=1; i<stalls.size(); i++) {
        int currStall = stalls[i];

        // If distance between current stall and last placed stall is less than min distance, we cannot place cow here
        // Only place cow on curr stall if the distance between curr and prev stall is greater than or equal to our min distance
        if (currStall - stalls[lastPlacedIndex] >= minDistance) {
            placedCows++;
            lastPlacedIndex = i;
        }

        // If k cows are placed return true
        if (placedCows >= k) return true;
    }

    // Return false as k cows were not placed
    return false;
}

int solve(int n, int k, vector<int> &stalls) {

    // Sort the stalls from minimum to maximum distance for easier allocation of cows
    sort(stalls.begin(), stalls.end());

    // Define Search space which is 0 to the maximum distance between first and last stall
    int left = 0;
    int right = stalls.back();

    int ans = -1;

    // Using Binary Search to figure out distance between any 2 cows such that all cows can be placed in the given stalls
    while (left <= right) {
        int currDistance = left + (right - left) / 2;

        // If cows can be placed with curr distance as gap between them, store it as ans and try to increase the distance between them
        if (canPlace(n, k, stalls, currDistance)) {
            ans = currDistance;
            left = currDistance + 1;
        }
        // If cows cannot be placed with curr distance as gap, reduce the distance as we only have limited stalls
        else {
            right = currDistance - 1;
        }
    }

    return ans;
}


int main() {

    

    return 0;
}