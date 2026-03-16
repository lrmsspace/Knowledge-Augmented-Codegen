// Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
//
//
// 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
// 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
//
//
// Return the total number of such pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 10
//
// Explanation:
//
// The subsequence pairs which have the GCD of their elements equal to 1 are:
//
//
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 200
//

class Solution {
    public int subsequencePairCount(int[] nums) {
        int MOD = 1_000_000_007;
        int maxNum = 200;
        int n = nums.length;

        // freq[g] will store the count of numbers in nums that are multiples of g
        int[] freq = new int[maxNum + 1];
        for (int num : nums) {
            for (int g = 1; g <= maxNum; g++) {
                if (num % g == 0) {
                    freq[g]++;
                }
            }
        }

        // dp[g] will store the number of non-empty subsequences with GCD exactly g
        long[] dp = new long[maxNum + 1];
        for (int g = maxNum; g >= 1; g--) {
            long totalSubseq = modPow(2, freq[g], MOD) - 1; // Total non-empty subsequences from multiples of g
            for (int multiple = 2 * g; multiple <= maxNum; multiple += g) {
                totalSubseq = (totalSubseq - dp[multiple] + MOD) % MOD; // Subtract subsequences counted for multiples of g
            }
            dp[g] = totalSubseq;
        }

        long result = 0;
        for (int g = 1; g <= maxNum; g++) {
            if (dp[g] > 0) {
                long count = dp[g];
                result = (result + count * (count - 1)) % MOD; // Count pairs (seq1, seq2)
            }
        }

        return (int) result;            
    }
}
