// Source: https://leetcode.com/problems/count-good-numbers/   |   Difficulty: Medium
//
// Problem Description:
// A digit string is good if the digits (0-indexed) at even indices are even and the digits at odd indices are prime (2, 3, 5, or 7).
//
//
// 	For example, "2582" is good because the digits (2 and 8) at even positions are even and the digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an even index but is not even.
//
//
// Given an integer n, return the total number of good digit strings of length n. Since the answer may be large, return it modulo 109 + 7.
//
// A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".
//
// Constraints:
// 1 <= n <= 1015
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - Chinese Remainder Theorem (number, mod-exp)
//   • When to use: Used to find an integer that satisfies a system of multiple congruence relations, particularly when the moduli are pairwise coprime. It's essential for reconstructing numbers from their remainders.
//   • Idea: The Chinese Remainder Theorem finds a unique integer solution to a system of linear congruences, modulo the product of their pairwise coprime moduli. It iteratively combines congruences, often using the Extended Euclidean Algorithm for modular inverses, with a complexity polynomial in the number of congruences.
//   • Invariants: The current combined solution satisfies all previously processed congruences.; The current combined modulus is the product of all previously processed pairwise coprime moduli.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
//   • Pitfalls: Forgetting to check if moduli are pairwise coprime, leading to no unique solution or no solution.; Incorrectly calculating modular inverses, which is crucial for the algorithm.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private long modExp(long base, long exp, long mod) {
        long result = 1;
        base = base % mod;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }
    public int countGoodNumbers(long n) {
        long mod = 1_000_000_007;
        long evenCount = (n + 1) / 2; // Count of even indices
        long oddCount = n / 2;        // Count of odd indices

        long evenChoices = modExp(5, evenCount, mod); // 5 choices for even indices (0,2,4,6,8)
        long oddChoices = modExp(4, oddCount, mod);   // 4 choices for odd indices (2,3,5,7)

        return (int)((evenChoices * oddChoices) % mod);         
    }
}
