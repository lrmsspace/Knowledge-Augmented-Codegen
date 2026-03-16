// Source: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of all the arithmetic subsequences of nums.
//
// A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
//
//
// 	For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
// 	For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
//
//
// A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
//
//
// 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
//
//
// The test cases are generated so that the answer fits in 32-bit integer.
//
// Example:
// Input: nums = [2,4,6,8,10]
// Output: 7
// Explanation: All arithmetic subsequence slices are:
// [2,4,6]
// [4,6,8]
// [6,8,10]
// [2,4,6,8]
// [4,6,8,10]
// [2,4,6,8,10]
// [2,6,10]
//
// Constraints:
// 1  <= nums.length <= 1000
// 	-231 <= nums[i] <= 231 - 1
//

class Solution {
    public int numberOfArithmeticSlices(int[] nums) {
        int n = nums.length;
        int result = 0;
        Map<Long, Integer>[] dp = new Map[n];

        for (int i = 0; i < n; i++) {
            dp[i] = new HashMap<>();
            for (int j = 0; j < i; j++) {
                long diff = (long) nums[i] - (long) nums[j];
                int countAtJ = dp[j].getOrDefault(diff, 0);
                int countAtI = dp[i].getOrDefault(diff, 0);

                result += countAtJ;
                dp[i].put(diff, countAtI + countAtJ + 1);
            }
        }

        return result;          
    }
}
