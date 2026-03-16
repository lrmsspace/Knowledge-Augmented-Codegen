// Source: https://leetcode.com/problems/make-array-non-decreasing/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. In one operation, you can select a subarray and replace it with a single element equal to its maximum value.
//
// Return the maximum possible size of the array after performing zero or more operations such that the resulting array is non-decreasing.
//
// Example:
// Input: nums = [4,2,5,3,5]
//
// Output: 3
//
// Explanation:
//
// One way to achieve the maximum size is:
//
//
// 	Replace subarray nums[1..2] = [2, 5] with 5 → [4, 5, 3, 5].
// 	Replace subarray nums[2..3] = [3, 5] with 5 → [4, 5, 5].
//
//
// The final array [4, 5, 5] is non-decreasing with size 3.
//
// Constraints:
// 1 <= nums.length <= 2 * 105
// 	1 <= nums[i] <= 2 * 105
//

class Solution {
    public int maximumPossibleSize(int[] nums) {
        int n = nums.length;
        int count = 1; // At least one element will always be there
        int currentMax = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i] >= currentMax) {
                count++;
                currentMax = nums[i];
            }
        }

        return count;           
    }
}
