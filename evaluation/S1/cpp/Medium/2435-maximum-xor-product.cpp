// Source: https://leetcode.com/problems/maximum-xor-product/   |   Difficulty: Medium
//
// Problem Description:
// Given three integers a, b, and n, return the maximum value of (a XOR x) * (b XOR x) where 0 <= x < 2n.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Note that XOR is the bitwise XOR operation.
//
// Example:
// Input: a = 12, b = 5, n = 4
// Output: 98
// Explanation: For x = 2, (a XOR x) = 14 and (b XOR x) = 7. Hence, (a XOR x) * (b XOR x) = 98. 
// It can be shown that 98 is the maximum value of (a XOR x) * (b XOR x) for all 0 <= x < 2n.
//
// Constraints:
// 0 <= a, b < 250
// 	0 <= n <= 50
//
// Helpful references (internal KB):
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
// - Fibonacci Numbers (number, greedy, enumeration)
//   • When to use: When you need a unique, non-ambiguous binary representation of positive integers based on Fibonacci numbers, ensuring no two consecutive Fibonacci numbers are used in the sum.
//   • Idea: This algorithm encodes a positive integer into a unique binary string by greedily finding its Zeckendorf representation (sum of non-consecutive Fibonacci numbers). The encoding process typically involves iterating through Fibonacci numbers, resulting in a logarithmic time complexity relative to the input number's magnitude.
//   • Invariants: The remaining value 'n' to be encoded is always non-negative.; The partial binary code constructed so far represents a valid Zeckendorf sum of non-consecutive Fibonacci numbers.
//   • Tips: Precompute Fibonacci numbers up to a certain limit to optimize lookups.; Always start with the largest Fibonacci number less than or equal to the target value.
//   • Pitfalls: Incorrectly handling the base cases for small numbers like 1 or 2.; Forgetting to append the mandatory final '1' bit to the codeword.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximumXorProduct(long long a, long long b, int n) {
        const long long MOD = 1000000007;
        long long limit = 1LL << n;
        long long x = 0;
        for (int i = n - 1; i >= 0; --i) {
            long long bit = 1LL << i;
            long long a_bit = (a & bit) ? 1 : 0;
            long long b_bit = (b & bit) ? 1 : 0;
            if (a_bit == b_bit) {
                // both 0 or both 1
                // set x_bit to 1 to maximize both (a XOR x) and (b XOR x)
                x |= bit;
            }
            // else one is 0, one is 1
            // set x_bit to 0 to maximize product
        }
        long long res_a = (a ^ x) % MOD;
        long long res_b = (b ^ x) % MOD;
        return (int)((res_a * res_b) % MOD);            
    }
};
