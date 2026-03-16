// Source: https://leetcode.com/problems/minimum-right-shifts-to-sort-the-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array nums of length n containing distinct positive integers. Return the minimum number of right shifts required to sort nums and -1 if this is not possible.
//
// A right shift is defined as shifting the element at index i to index (i + 1) % n, for all indices.
//
// Example:
// Input: nums = [3,4,5,1,2]
// Output: 2
// Explanation: 
// After the first right shift, nums = [2,3,4,5,1].
// After the second right shift, nums = [1,2,3,4,5].
// Now nums is sorted; therefore the answer is 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	nums contains distinct integers.
//

class Solution {
public:
    int minimumRightShifts(vector<int>& nums) {
        int n = nums.size();
        int count = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                count++;
            }
        }
        if (count == 0) {
            return 0; // Already sorted
        }
        if (count > 1) {
            return -1; // More than one drop, cannot be sorted by right shifts
        }
        // Find the index where the drop occurs
        int dropIndex = -1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                dropIndex = i;
                break;
            }
        }
        // Check if the array can be sorted by right shifts
        if (nums[n - 1] > nums[0]) {
            return -1; // Last element must be less than or equal to first element after rotation
        }
        return n - dropIndex; // Minimum right shifts needed            
    }
};
