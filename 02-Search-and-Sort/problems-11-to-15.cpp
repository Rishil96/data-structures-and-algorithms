#include <iostream>
#include <vector>
using namespace std;


// 11. Single Unique element in an array of element pairs
int singleNonDuplicate(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        // Odd Case
        if (mid & 1) {
            // If mid element is equal to mid + 1 element, it means we are on right side of unique element
            if (mid + 1 < nums.size() && nums[mid] == nums[mid + 1]) {
                right = mid;
            }
            // Else we are on left side
            else {
                left = mid + 1;
            }
        }
        // Even Case
        else {
            // If mid element is equal to mid + 1 element, we are on left side of unique element
            if (mid + 1 < nums.size() && nums[mid] == nums[mid + 1]) {
                left = mid + 1;
            }
            // Else we are on right side
            else {
                right = mid;
            }
        }
    }

    return nums[right];
}


// 12. 


// 13. 

int main() {

    

    return 0;
}