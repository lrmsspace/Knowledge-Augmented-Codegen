// Source: https://leetcode.com/problems/the-number-of-good-subsets/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. We call a subset of nums good if its product can be represented as a product of one or more distinct prime numbers.
//
//
// 	For example, if nums = [1, 2, 3, 4]:
//
// 	
// 		[2, 3], [1, 2, 3], and [1, 3] are good subsets with products 6 = 2*3, 6 = 2*3, and 3 = 3 respectively.
// 		[1, 4] and [4] are not good subsets with products 4 = 2*2 and 4 = 2*2 respectively.
// 	
// 	
//
//
// Return the number of different good subsets in nums modulo 109 + 7.
//
// A subset of nums is any array that can be obtained by deleting some (possibly none or all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 6
// Explanation: The good subsets are:
// - [1,2]: product is 2, which is the product of distinct prime 2.
// - [1,2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [1,3]: product is 3, which is the product of distinct prime 3.
// - [2]: product is 2, which is the product of distinct prime 2.
// - [2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [3]: product is 3, which is the product of distinct prime 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 30
//

class Solution {
    public int numberOfGoodSubsets(int[] nums) {
        int mod = (int)1e9 + 7;
        int[] primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        int n = primes.length;

        int[] count = new int[31];
        for (int num : nums) {
            count[num]++;
        }

        long[] dp = new long[1 << n];
        dp[0] = 1;

        for (int num = 2; num <= 30; num++) {
            if (count[num] == 0) continue;

            int subsetMask = 0;
            boolean isValid = true;

            for (int j = 0; j < n; j++) {
                int prime = primes[j];
                int primeCount = 0;
                int tempNum = num;

                while (tempNum % prime == 0) {
                    tempNum /= prime;
                    primeCount++;
                }

                if (primeCount > 1) {
                    isValid = false;
                    break;
                } else if (primeCount == 1) {
                    subsetMask |= (1 << j);
                }
            }

            if (!isValid) continue;

            for (int mask = (1 << n) - 1; mask >= 0; mask--) {
                if ((mask & subsetMask) == 0) {
                    dp[mask | subsetMask] = (dp[mask | subsetMask] + dp[mask] * count[num]) % mod;
                }
            }
        }

        long result = 0;
        for (int mask = 1; mask < (1 << n); mask++) {
            result = (result + dp[mask]) % mod;
        }

        if (count[1] > 0) {
            long pow2 = 1;
            for (int i = 0; i < count[1]; i++) {
                pow2 = (pow2 * 2) % mod;
            }
            result = (result * pow2) % mod;
        }

        return (int)result;         
    }
}
