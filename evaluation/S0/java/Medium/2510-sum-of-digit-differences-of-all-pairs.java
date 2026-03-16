// Source: https://leetcode.com/problems/sum-of-digit-differences-of-all-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers where all integers have the same number of digits.
//
// The digit difference between two integers is the count of different digits that are in the same position in the two integers.
//
// Return the sum of the digit differences between all pairs of integers in nums.
//
// Example:
// Input: nums = [13,23,12]
//
// Output: 4
//
// Explanation:
// We have the following:
// - The digit difference between 13 and 23 is 1.
// - The digit difference between 13 and 12 is 1.
// - The digit difference between 23 and 12 is 2.
// So the total sum of digit differences between all pairs of integers is 1 + 1 + 2 = 4.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] < 109
// 	All integers in nums have the same number of digits.
//

class Solution {
    public long sumDigitDifferences(int[] nums) {
        int n = nums.length;
        int d = String.valueOf(nums[0]).length(); // Number of digits in each number
        long result = 0;

        // Iterate over each digit position
        for (int pos = 0; pos < d; pos++) {
            int[] count = new int[10]; // Count of each digit (0-9) at current position

            // Count occurrences of each digit at the current position
            for (int num : nums) {
                int digit = (num / (int) Math.pow(10, pos)) % 10;
                count[digit]++;
            }

            // Calculate the contribution of this digit position to the result
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (i != j) {
                        result += (long) count[i] * count[j];
                    }
                }
            }
        }

        return result;          
    }
}
