// Source: https://leetcode.com/problems/sum-of-floored-pairs/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the sum of floor(nums[i] / nums[j]) for all pairs of indices 0 <= i, j < nums.length in the array. Since the answer may be too large, return it modulo 109 + 7.
//
// The floor() function returns the integer part of the division.
//
// Example:
// Input: nums = [2,5,9]
// Output: 10
// Explanation:
// floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
// floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
// floor(5 / 2) = 2
// floor(9 / 2) = 4
// floor(9 / 5) = 1
// We calculate the floor of the division for every pair of indices in the array then sum them up.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
    public int sumOfFlooredPairs(int[] nums) {
        int MOD = 1_000_000_007;
        int maxNum = 0;
        for (int num : nums) {
            maxNum = Math.max(maxNum, num);
        }

        int[] freq = new int[maxNum + 1];
        for (int num : nums) {
            freq[num]++;
        }

        int[] prefixFreq = new int[maxNum + 1];
        for (int i = 1; i <= maxNum; i++) {
            prefixFreq[i] = prefixFreq[i - 1] + freq[i];
        }

        long result = 0;
        for (int i = 1; i <= maxNum; i++) {
            if (freq[i] == 0) continue;

            for (int multiple = i; multiple <= maxNum; multiple += i) {
                int left = multiple;
                int right = Math.min(multiple + i - 1, maxNum);
                int countInRange = prefixFreq[right] - prefixFreq[left - 1];
                result = (result + (long) freq[i] * countInRange * (multiple / i)) % MOD;
            }
        }

        return (int) result;            
    }
}
