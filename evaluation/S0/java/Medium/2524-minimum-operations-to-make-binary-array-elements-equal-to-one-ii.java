// Source: https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// You can do the following operation on the array any number of times (possibly zero):
//
//
// 	Choose any index i from the array and flip all the elements from index i to the end of the array.
//
//
// Flipping an element means changing its value from 0 to 1, and from 1 to 0.
//
// Return the minimum number of operations required to make all elements in nums equal to 1.
//
// Example:
// Input: nums = [0,1,1,0,1]
//
// Output: 4
//
// Explanation:
// We can do the following operations:
//
//
// 	Choose the index i = 1. The resulting array will be nums = [0,0,0,1,0].
// 	Choose the index i = 0. The resulting array will be nums = [1,1,1,0,1].
// 	Choose the index i = 4. The resulting array will be nums = [1,1,1,0,0].
// 	Choose the index i = 3. The resulting array will be nums = [1,1,1,1,1].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 1
//

class Solution {
    public int minOperations(int[] nums) {
        int operations = 0;
        int n = nums.length;

        for (int i = n - 1; i >= 0; i--) {
            if (nums[i] == operations % 2) {
                operations++;
            }
        }

        return operations;          
    }
}
