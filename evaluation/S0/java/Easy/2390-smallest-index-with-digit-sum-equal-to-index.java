// Source: https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums.
//
// Return the smallest index i such that the sum of the digits of nums[i] is equal to i.
//
// If no such index exists, return -1.
//
// Example:
// Input: nums = [1,3,2]
//
// Output: 2
//
// Explanation:
//
//
// 	For nums[2] = 2, the sum of digits is 2, which is equal to index i = 2. Thus, the output is 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 1000
//

class Solution {
    public int smallestIndex(int[] nums) {
        for (int i = 0; i < nums.length; i++) {
            if (digitSum(nums[i]) == i) {
                return i;
            }
        }
        return -1;          
    }
}
