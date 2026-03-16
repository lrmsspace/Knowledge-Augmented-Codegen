// Source: https://leetcode.com/problems/subsequences-with-a-unique-middle-mode-i/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, find the number of subsequences of size 5 of nums with a unique middle mode.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// A mode of a sequence of numbers is defined as the element that appears the maximum number of times in the sequence.
//
// A sequence of numbers contains a unique mode if it has only one mode.
//
// A sequence of numbers seq of size 5 contains a unique middle mode if the middle element (seq[2]) is a unique mode.
//
// Example:
// Input: nums = [1,1,1,1,1,1]
//
// Output: 6
//
// Explanation:
//
// [1, 1, 1, 1, 1] is the only subsequence of size 5 that can be formed, and it has a unique middle mode of 1. This subsequence can be formed in 6 different ways, so the output is 6.
//
// Constraints:
// 5 <= nums.length <= 1000
//  -109 <= nums[i] <= 109
//

class Solution {
    public int subsequencesWithMiddleMode(int[] nums) {
        int mod = (int)1e9 + 7;
        int n = nums.length;
        long result = 0;

        for (int mid = 2; mid <= n - 3; mid++) {
            int midValue = nums[mid];

            // Count elements less than midValue on the left and right
            long leftLess = 0, leftEqual = 0;
            long rightLess = 0, rightEqual = 0;

            for (int i = 0; i < mid; i++) {
                if (nums[i] < midValue) leftLess++;
                else if (nums[i] == midValue) leftEqual++;
            }

            for (int i = mid + 1; i < n; i++) {
                if (nums[i] < midValue) rightLess++;
                else if (nums[i] == midValue) rightEqual++;
            }

            // Calculate combinations
            long ways = 0;

            // Case 1: Two less on the left, two less on the right
            ways += (leftLess * (leftLess - 1) / 2) * (rightLess * (rightLess - 1) / 2);

            // Case 2: Two less on the left, one less and one equal on the right
            ways += (leftLess * (leftLess - 1) / 2) * (rightLess * rightEqual);

            // Case 3: One less and one equal on the left, two less on the right
            ways += (leftLess * leftEqual) * (rightLess * (rightLess - 1) / 2);

            // Case 4: One less and one equal on the left, one less and one equal on the right
            ways += (leftLess * leftEqual) * (rightLess * rightEqual);

            result = (result + ways) % mod;
        }

        return (int)result;         
    }
}
