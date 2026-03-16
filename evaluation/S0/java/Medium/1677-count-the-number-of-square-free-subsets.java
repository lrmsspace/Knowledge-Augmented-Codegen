// Source: https://leetcode.com/problems/count-the-number-of-square-free-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer 0-indexed array nums.
//
// A subset of the array nums is square-free if the product of its elements is a square-free integer.
//
// A square-free integer is an integer that is divisible by no square number other than 1.
//
// Return the number of square-free non-empty subsets of the array nums. Since the answer may be too large, return it modulo 109 + 7.
//
// A non-empty subset of nums is an array that can be obtained by deleting some (possibly none but not all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [3,4,4,5]
// Output: 3
// Explanation: There are 3 square-free subsets in this example:
// - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
// - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
// - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
// It can be proven that there are no more than 3 square-free subsets in the given array.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 30
//

class Solution {
    public int squareFreeSubsets(int[] nums) {
        int MOD = (int)1e9 + 7;
        int[] count = new int[31];
        for (int num : nums) {
            count[num]++;
        }

        int[] primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        int n = primes.length;
        long[] dp = new long[1 << n];
        dp[0] = 1;

        for (int num = 2; num <= 30; num++) {
            if (count[num] == 0) continue;

            int subsetMask = 0;
            boolean isSquareFree = true;

            for (int i = 0; i < n; i++) {
                int prime = primes[i];
                int primeSquare = prime * prime;

                if (num % primeSquare == 0) {
                    isSquareFree = false;
                    break;
                } else if (num % prime == 0) {
                    subsetMask |= (1 << i);
                }
            }

            if (!isSquareFree) continue;

            for (int mask = (1 << n) - 1; mask >= 0; mask--) {
                if ((mask & subsetMask) == 0) {
                    dp[mask | subsetMask] = (dp[mask | subsetMask] + dp[mask] * count[num]) % MOD;
                }
            }
        }

        long result = 0;
        for (int mask = 1; mask < (1 << n); mask++) {
            result = (result + dp[mask]) % MOD;
        }

        if (count[1] > 0) {
            long pow2 = 1;
            for (int i = 0; i < count[1]; i++) {
                pow2 = (pow2 * 2) % MOD;
            }
            result = (result * pow2) % MOD;
        }

        return (int)result;         
    }
}
