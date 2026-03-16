// Source: https://leetcode.com/problems/max-pair-sum-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. You have to find the maximum sum of a pair of numbers from nums such that the largest digit in both numbers is equal.
//
// For example, 2373 is made up of three distinct digits: 2, 3, and 7, where 7 is the largest among them.
//
// Return the maximum sum or -1 if no such pair exists.
//
// Example:
// Input: nums = [112,131,411]
//
// Output: -1
//
// Explanation:
//
// Each numbers largest digit in order is [2,3,4].
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 104
//

class Solution {
    public int maxSum(int[] nums) {
        int[] maxDigits = new int[10];
        int result = -1;

        for (int num : nums) {
            int largestDigit = getLargestDigit(num);

            if (maxDigits[largestDigit] != 0) {
                result = Math.max(result, num + maxDigits[largestDigit]);
            }

            maxDigits[largestDigit] = Math.max(maxDigits[largestDigit], num);
        }

        return result;          
    }
}
