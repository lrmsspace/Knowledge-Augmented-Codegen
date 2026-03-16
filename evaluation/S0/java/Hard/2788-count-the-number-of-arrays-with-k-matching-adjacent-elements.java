// Source: https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers n, m, k. A good array arr of size n is defined as follows:
//
//
// 	Each element in arr is in the inclusive range [1, m].
// 	Exactly k indices i (where 1 <= i < n) satisfy the condition arr[i - 1] == arr[i].
//
//
// Return the number of good arrays that can be formed.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, m = 2, k = 1
//
// Output: 4
//
// Explanation:
//
//
// 	There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and [2, 2, 1].
// 	Hence, the answer is 4.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= m <= 105
// 	0 <= k <= n - 1
//

class Solution {
    public int countGoodArrays(int n, int m, int k) {
        long MOD = 1_000_000_007;

        // Precompute factorials and their modular inverses
        long[] fact = new long[n + 1];
        long[] invFact = new long[n + 1];
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invFact[n] = modInverse(fact[n], MOD);
        for (int i = n - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        // Function to compute nCr % MOD
        long nCr(int n, int r) {
            if (r > n || r < 0) return 0;
            return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
        }

        // Calculate the number of good arrays
        long waysToChoosePositions = nCr(n - 1, k);
        long waysToFillArray = (m * modPow(m - 1, n - k - 1, MOD)) % MOD;

        return (int) ((waysToChoosePositions * waysToFillArray) % MOD);         
    }
}
