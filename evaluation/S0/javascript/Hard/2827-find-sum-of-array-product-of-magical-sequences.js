// Source: https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, m and k, and an integer array nums.
// A sequence of integers seq is called magical if:
//
//
// 	seq has a size of m.
// 	0 <= seq[i] < nums.length
// 	The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.
//
//
// The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).
//
// Return the sum of the array products for all valid magical sequences.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A set bit refers to a bit in the binary representation of a number that has a value of 1.
//
// Example:
// Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
//
// Output: 991600007
//
// Explanation:
//
// All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 1013.
//
// Constraints:
// 1 <= k <= m <= 30
// 	1 <= nums.length <= 50
// 	1 <= nums[i] <= 108
//

/**
 * @param {number} m
 * @param {number} k
 * @param {number[]} nums
 * @return {number}
 */
var magicalSum = function(m, k, nums) {
    const MOD = 1e9 + 7;
    const n = nums.length;
    const dp = Array.from({ length: m + 1 }, () => Array(k + 1).fill(0));
    dp[0][0] = 1;
    for (let len = 1; len <= m; len++) {
        for (let bits = 0; bits <= k; bits++) {
            for (let i = 0; i < n; i++) {
                const bitCount = (i & -i).toString(2).length - 1;
                if (bits - bitCount >= 0) {
                    dp[len][bits] = (dp[len][bits] + dp[len - 1][bits - bitCount] * nums[i]) % MOD;
                }
            }
        }
    }
    return dp[m][k];
};
