// Source: https://leetcode.com/problems/difference-between-element-sum-and-digit-sum-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer array nums.
//
//
// 	The element sum is the sum of all the elements in nums.
// 	The digit sum is the sum of all the digits (not necessarily distinct) that appear in nums.
//
//
// Return the absolute difference between the element sum and digit sum of nums.
//
// Note that the absolute difference between two integers x and y is defined as |x - y|.
//
// Example:
// Input: nums = [1,15,6,3]
// Output: 9
// Explanation: 
// The element sum of nums is 1 + 15 + 6 + 3 = 25.
// The digit sum of nums is 1 + 1 + 5 + 6 + 3 = 16.
// The absolute difference between the element sum and digit sum is |25 - 16| = 9.
//
// Constraints:
// 1 <= nums.length <= 2000
// 	1 <= nums[i] <= 2000
//

class Solution {
    public int differenceOfSum(int[] nums) {
        int elementSum = 0;
        int digitSum = 0;

        for (int num : nums) {
            elementSum += num;

            while (num > 0) {
                digitSum += num % 10;
                num /= 10;
            }
        }

        return Math.abs(elementSum - digitSum);         
    }
}
