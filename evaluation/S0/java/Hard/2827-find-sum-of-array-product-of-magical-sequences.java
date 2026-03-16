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

class Solution {
    public int magicalSum(int m, int k, int[] nums) {
        int MOD = 1_000_000_007;
        int n = nums.length;

        long[] dp = new long[m + 1];
        dp[0] = 1;

        for (int num : nums) {
            long[] next = new long[m + 1];
            long val = 1;
            for (int count = 1; count <= m; count++) {
                val = (val * num) % MOD;
                for (int used = 0; used + count <= m; used++) {
                    next[used + count] = (next[used + count] + dp[used] * val) % MOD;
                }
            }
            for (int i = 0; i <= m; i++) {
                dp[i] = (dp[i] + next[i]) % MOD;
            }
        }

        long result = 0;
        for (int bits = 0; bits <= m; bits++) {
            if (Integer.bitCount(bits) == k) {
                result = (result + dp[bits]) % MOD;
            }
        }

        return (int) result;            
    }
}
