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
// Helpful references (internal KB):
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - Binomial Coefficients (array, number, dp-1d, mod-exp)
//   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
//   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
//   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
//   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
//   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
// - Binomial Coefficients (number, recursion)
//   • When to use: Use when computing C(n, k) modulo m where n is large and m is small, especially when m is prime, a prime power, or a composite number with small prime factors.
//   • Idea: This technique computes binomial coefficients C(n, k) modulo m, particularly when n is very large and m is small. It leverages modular arithmetic properties, such as Lucas's Theorem for prime moduli or the Chinese Remainder Theorem for composite moduli, achieving complexities like O(m + log_m n).
//   • Invariants: For C(N, K) mod M, the recursive calls C(N/M, K/M) and C(N%M, K%M) are valid subproblems.; All factorial and inverse factorial values used for C(x, y) where x, y < M are precomputed modulo M.
//   • Tips: Precompute factorials and inverse factorials modulo m for efficient base case calculations.; Apply Lucas's Theorem when the modulus m is prime to break down the problem recursively.
//   • Pitfalls: Failing to handle k > n correctly, which should yield 0.; Incorrectly applying Lucas's Theorem when the modulus is not prime.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        const int MOD = 1000000007;
        long long result = 1;
        int i;

        if (k > n - 1) {
            return 0;
        }

        for (i = 0; i < k; ++i) {
            result = (result * (n - 1 - i)) % MOD;
        }
        for (i = 0; i < k + 1; ++i) {
            result = (result * m) % MOD;
        }
        for (i = 0; i < k; ++i) {
            result = (result * modInverse(i + 1, MOD)) % MOD;
        }

        return (int)result;         
    }
};
