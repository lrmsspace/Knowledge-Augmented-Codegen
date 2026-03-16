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
// Helpful references (internal KB):
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
//   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
//   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
//   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
//   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private long modInverse(long a, long mod) {
        long m0 = mod, t, q;
        long x0 = 0, x1 = 1;

        if (mod == 1) return 0;

        while (a > 1) {
            q = a / mod;
            t = mod;

            mod = a % mod;
            a = t;
            t = x0;

            x0 = x1 - q * x0;
            x1 = t;
        }

        if (x1 < 0) x1 += m0;

        return x1;
    }
    private long nCr(int n, int r, long[] fact, long[] invFact, int mod) {
        if (r > n || r < 0) return 0;
        return fact[n] * invFact[r] % mod * invFact[n - r] % mod;
    }
    public int idealArrays(int n, int maxValue) {
        final int MOD = 1_000_000_007;

        // Precompute factorials and modular inverses for combinations
        long[] fact = new long[n + 50];
        long[] invFact = new long[n + 50];
        fact[0] = 1;
        for (int i = 1; i < fact.length; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invFact[invFact.length - 1] = modInverse(fact[invFact.length - 1], MOD);
        for (int i = invFact.length - 2; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        // Linear Sieve to get smallest prime factors
        int[] lp = new int[maxValue + 1];
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= maxValue; i++) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes.add(i);
            }
            for (int p : primes) {
                if (p > lp[i] || p * i > maxValue) break;
                lp[p * i] = p;
            }
        }

        long result = 0;
        for (int start = 1; start <= maxValue; start++) {
            Map<Integer, Integer> primeCount = new HashMap<>();
            int x = start;
            while (x > 1) {
                primeCount.put(lp[x], primeCount.getOrDefault(lp[x], 0) + 1);
                x /= lp[x];
            }

            long ways = 1;
            for (int count : primeCount.values()) {
                ways = ways * nCr(n - 1 + count, count, fact, invFact, MOD) % MOD;
            }
            result = (result + ways) % MOD;
        }

        return (int) result;            
    }
}
