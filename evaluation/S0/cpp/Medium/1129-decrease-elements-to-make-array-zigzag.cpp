// Source: https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.
//
// An array A is a zigzag array if either:
//
//
//  Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
//  OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
//
//
// Return the minimum number of moves to transform the given array nums into a zigzag array.
//
// Example:
// Input: nums = [1,2,3]
// Output: 2
// Explanation: We can decrease 2 to 0 or 3 to 1.
//
// Constraints:
// 1 <= nums.length <= 1000
//  1 <= nums[i] <= 1000
//

class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
        int n = nums.size();
        int movesEven = 0; // Make even indices greater
        int movesOdd = 0;  // Make odd indices greater

        for (int i = 0; i < n; ++i) {
            int decrease = 0;
            if (i % 2 == 0) { // Even index
                if (i > 0 && nums[i] >= nums[i - 1]) {
                    decrease = nums[i] - nums[i - 1] + 1;
                }
                if (i < n - 1 && nums[i] >= nums[i + 1]) {
                    decrease = max(decrease, nums[i] - nums[i + 1] + 1);
                }
                movesEven += decrease;
            } else { // Odd index
                if (i > 0 && nums[i] >= nums[i - 1]) {
                    decrease = nums[i] - nums[i - 1] + 1;
                }
                if (i < n - 1 && nums[i] >= nums[i + 1]) {
                    decrease = max(decrease, nums[i] - nums[i + 1] + 1);
                }
                movesOdd += decrease;
            }
        }

        return min(movesEven, movesOdd);            
    }
};
