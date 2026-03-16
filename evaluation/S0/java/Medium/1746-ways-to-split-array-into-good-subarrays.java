// Source: https://leetcode.com/problems/ways-to-split-array-into-good-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// A subarray of an array is good if it contains exactly one element with the value 1.
//
// Return an integer denoting the number of ways to split the array nums into good subarrays. As the number may be too large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [0,1,0,0,1]
// Output: 3
// Explanation: There are 3 ways to split nums into good subarrays:
// - [0,1] [0,0,1]
// - [0,1,0] [0,1]
// - [0,1,0,0] [1]
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 1
//

class Solution {
    public int numberOfGoodSubarraySplits(int[] nums) {
        final int MOD = 1_000_000_007;
        long result = 1;
        int countZeros = 0;
        boolean foundOne = false;

        for (int num : nums) {
            if (num == 1) {
                if (foundOne) {
                    result = (result * (countZeros + 1)) % MOD;
                } else {
                    foundOne = true;
                }
                countZeros = 0;
            } else {
                if (foundOne) {
                    countZeros++;
                }
            }
        }

        return foundOne ? (int) result : 0;         
    }
}
