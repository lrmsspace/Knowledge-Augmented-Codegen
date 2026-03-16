// Source: https://leetcode.com/problems/string-transformation/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and t of equal length n. You can perform the following operation on the string s:
//
//
// 	Remove a suffix of s of length l where 0 < l < n and append it at the start of s.
// 	For example, let s = 'abcd' then in one operation you can remove the suffix 'cd' and append it in front of s making s = 'cdab'.
//
//
// You are also given an integer k. Return the number of ways in which s can be transformed into t in exactly k operations.
//
// Since the answer can be large, return it modulo 109 + 7.
//
// Example:
// Input: s = "abcd", t = "cdab", k = 2
// Output: 2
// Explanation: 
// First way:
// In first operation, choose suffix from index = 3, so resulting s = "dabc".
// In second operation, choose suffix from index = 3, so resulting s = "cdab".
//
// Second way:
// In first operation, choose suffix from index = 1, so resulting s = "bcda".
// In second operation, choose suffix from index = 1, so resulting s = "cdab".
//
// Constraints:
// 2 <= s.length <= 5 * 105
// 	1 <= k <= 1015
// 	s.length == t.length
// 	s and t consist of only lowercase English alphabets.
//
// Helpful references (internal KB):
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numberOfWays(string s, string t, long long k) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        long long same = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == t[i]) ++same;
        }
        long long diff = n - same;

        // We need to solve the equations:
        // a + b = k
        // a - b = diff (mod n)
        // where a is the number of operations that result in same characters,
        // and b is the number of operations that result in different characters.
        // This gives us:
        // a = (k + diff) / 2
        // b = (k - diff) / 2
        // We need both a and b to be non-negative integers.

        long long a_plus_b = k;
        long long a_minus_b = diff;

        if ((a_plus_b + a_minus_b) % 2 != 0 || (a_plus_b - a_minus_b) % 2 != 0) {
            return 0;
        }

        long long a = (a_plus_b + a_minus_b) / 2;
        long long b = (a_plus_b - a_minus_b) / 2;

        if (a < 0 || b < 0) {
            return 0;
        }

        // Now we need to calculate C(k, a) * same^a * diff^b % MOD
        long long res = 1;

        // Calculate C(k, a) using Fermat's Little Theorem
        long long numerator = 1;
        long long denominator = 1;
        for (long long i = 0; i < a; ++i) {
            numerator = (numerator * (k - i)) % MOD;
            denominator = (denominator * (i + 1)) % MOD;
        }

        // Modular inverse of denominator
        long long denom_inv = 1;
        long long exp = MOD - 2; // Fermat's Little Theorem
        long long base = denominator;
        while (exp > 0) {
            if (exp % 2 == 1) {
                denom_inv = (denom_inv * base) % MOD;
            }
            base = (base * base) % MOD;
            exp /= 2;
        }
        long long comb = (numerator * denom_inv) % MOD;
        res = (comb * modPow(same, a, MOD)) % MOD;
        res = (res * modPow(diff, b, MOD)) % MOD;
        return static_cast<int>(res);
    }
};
