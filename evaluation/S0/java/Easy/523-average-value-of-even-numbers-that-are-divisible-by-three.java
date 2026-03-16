// Source: https://leetcode.com/problems/average-value-of-even-numbers-that-are-divisible-by-three/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums of positive integers, return the average value of all even integers that are divisible by 3.
//
// Note that the average of n elements is the sum of the n elements divided by n and rounded down to the nearest integer.
//
// Example:
// Input: nums = [1,3,6,10,12,15]
// Output: 9
// Explanation: 6 and 12 are even numbers that are divisible by 3. (6 + 12) / 2 = 9.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
//

class Solution {
    public int averageValue(int[] nums) {
        int sum = 0;
        int count = 0;

        for (int num : nums) {
            if (num % 6 == 0) { // Check if the number is even and divisible by 3
                sum += num;
                count++;
            }
        }

        return count == 0 ? 0 : sum / count; // Return 0 if no valid numbers found          
    }
}
