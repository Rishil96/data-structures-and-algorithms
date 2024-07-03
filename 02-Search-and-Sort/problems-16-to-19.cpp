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


// 18. EKO SPOJ
bool hasEnoughWood(int &N, int &M, int trees[], int &cutHeight) {
    
    int gatheredWood = 0;

    for (int i=0; i<N; i++) {
        if (trees[i] > cutHeight) gatheredWood += (trees[i] - cutHeight);
    }

    return gatheredWood >= M;
}

int ekoSPOJ(int &N, int M, int trees[]) {
    /*
        N -> no. of trees
        M -> required units of wood
        trees -> heights of trees in an array of size N
    */
    
    int ans = 0;

    // Define search space of wood
    int low = 0;
    int high = 0;

    // Lowest height from where the tree can be chopped is 0 and highest height is the height of the tallest tree
    for (int i=0; i<N; i++) high = max(high, trees[i]);

    // Use Binary Search to get the optimal height from where trees can be cut causing minimal wastage of wood
    while (low <= high) {
        int cutHeight = low + (high - low) / 2;

        if (hasEnoughWood(N, M, trees, cutHeight)) {
            ans = cutHeight;
            low = cutHeight + 1;
        }
        else {
            high = cutHeight - 1;
        }
    }

    return ans;
}


// 19. PRATA SPOJ
bool canCookPratas(int &P, int &L, int cookRanks[], int &timeBarrier) {
    int timeTaken = 0;
    int cookedPratas = 0;
    int cookTime;

    for (int i=0; i<L; i++) {
        int currRank = cookRanks[i];
        cookTime = currRank;
        
        // While current chef can cook pratas and is within time barrier, keep cooking 
        while (timeTaken + cookTime <= timeBarrier) {
            cookedPratas++;                             // Cook current prata
            timeTaken += cookTime;                      // Add time used to cook current prata
            cookTime += currRank;                       // Update the time required to cook next prata
            if (cookedPratas >= P) return true;         // Return true if order was complete
        }

        timeTaken = 0;
    }

    return false;
}

int prataSPOJ(int P, int L, int cookRanks[]) {
    /*
        P => no. of pratas ordered
        L => no. of cooks
        cookRanks => ranks of each cook
        A cook with rank R can cook first prata in time R, second prata in time 2R, third in 3R, and so on.
    */
    
    // Define a search space for total time taken
    int minTime = 0;
    int maxTime = 0;

    // Find the slowest cook
    for (int i=0; i<L; i++) maxTime = max(maxTime, cookRanks[i]);

    // Make the slowest cook to make all pratas
    // Use Summation of Sequence Formula : (n/2) * (2a + (n - 1) * d)
    /*
        n = no. of items in sequence to be added
        a = first term in the sequence
        d = difference between 2 consecutive terms
    */
    maxTime = (P/2) * (2 * maxTime + (P - 1) * maxTime);
    
    // Use Binary Search to find optimal time in which the pratas can be made
    int ans = -1;

    while (minTime <= maxTime) {
        int currTimeTaken = minTime + (maxTime - minTime) / 2;

        // If prata order can be cooked within current time, save it and try to minimize the time
        if (canCookPratas(P, L, cookRanks, currTimeTaken)) {
            ans = currTimeTaken;
            maxTime = currTimeTaken - 1;
        }
        // Increase the time if pratas were not cooked with current time
        else {
            minTime = currTimeTaken + 1;
        }
    }

    return ans;
}


int main() {

    int N = 4;
    int M = 7;
    int trees[] = {20, 15, 10, 17};

    cout << "EKO SPOJ 1: " << ekoSPOJ(N, M, trees) << endl;
    N = 5;
    M = 20;
    int trees2[] = {4, 42, 40, 26, 46};

    cout << "EKO SPOJ 2: " << ekoSPOJ(N, M, trees2) << endl;

    int P = 10;
    int L = 4;
    int cookRanks[] = {1, 2, 3, 4};

    cout << "PRATA SPOJ 1: " << prataSPOJ(P, L, cookRanks) << endl;

    P = 8;
    L = 1;
    int cookRanks2[] = {1};

    cout << "PRATA SPOJ 2: " << prataSPOJ(P, L, cookRanks2) << endl;

    P = 8;
    L = 8;
    int cookRanks3[] = {1, 1, 1, 1, 1, 1, 1, 1};

    cout << "PRATA SPOJ 3: " << prataSPOJ(P, L, cookRanks3) << endl;

    return 0;
}