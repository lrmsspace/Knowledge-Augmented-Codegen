// Source: https://leetcode.com/problems/count-the-number-of-ideal-arrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers n and maxValue, which are used to describe an ideal array.
//
// A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:
//
//
// 	Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
// 	Every arr[i] is divisible by arr[i - 1], for 0 < i < n.
//
//
// Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 2, maxValue = 5
// Output: 10
// Explanation: The following are the possible ideal arrays:
// - Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
// - Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
// - Arrays starting with the value 3 (1 array): [3,3]
// - Arrays starting with the value 4 (1 array): [4,4]
// - Arrays starting with the value 5 (1 array): [5,5]
// There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.
//
// Constraints:
// 2 <= n <= 104
// 	1 <= maxValue <= 104
//

class Solution {
    public int idealArrays(int n, int maxValue) {
        int MOD = 1_000_000_007;

        // Precompute factorials and inverse factorials for combinations
        long[] fact = new long[n + 20];
        long[] invFact = new long[n + 20];
        fact[0] = 1;
        for (int i = 1; i < fact.length; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invFact[invFact.length - 1] = modInverse(fact[invFact.length - 1], MOD);
        for (int i = invFact.length - 2; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        // Function to compute nCr % MOD
        java.util.function.BiFunction<Integer, Integer, Long> nCr = (N, R) -> {
            if (R > N || R < 0) return 0L;
            return fact[N] * invFact[R] % MOD * invFact[N - R] % MOD;
        };

        long result = 0;

        // Iterate over all possible starting values
        for (int start = 1; start <= maxValue; start++) {
            int val = start;
            int length = 1;

            // Count the number of ways to form ideal arrays starting with 'start'
            while (val <= maxValue) {
                result = (result + nCr.apply(n - 1, length - 1)) % MOD;
                val *= 2;
                length++;
            }
        }

        return (int) result;            
    }
}
