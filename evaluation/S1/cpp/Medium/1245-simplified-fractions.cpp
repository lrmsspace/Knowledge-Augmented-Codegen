// Source: https://leetcode.com/problems/simplified-fractions/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a list of all simplified fractions between 0 and 1 (exclusive) such that the denominator is less-than-or-equal-to n. You can return the answer in any order.
//
// Example:
// Input: n = 2
// Output: ["1/2"]
// Explanation: "1/2" is the only unique fraction with a denominator less-than-or-equal-to 2.
//
// Constraints:
// 1 <= n <= 100
//
// Helpful references (internal KB):
// - Continued fractions (number, enumeration, gcd)
//   • When to use: Use when seeking the best rational approximations of real numbers or solving certain Diophantine equations. It's also applied in number theory for analyzing properties of irrational numbers.
//   • Idea: Continued fractions represent a real number as a sum of an integer and the reciprocal of another number, recursively. This iterative process, based on the Euclidean algorithm, generates a sequence of best rational approximations.
//   • Invariants: The current convergent p_k / q_k is the best rational approximation for its denominator size.; The sequence of partial quotients a_i are integers, with a_i >= 1 for i > 0.
//   • Tips: Understand the relationship with the Euclidean algorithm for rational numbers.; Convergents provide the best rational approximations for a given denominator size.
//   • Pitfalls: Floating-point precision issues can significantly affect accuracy for real numbers.; Misinterpreting 'best approximation' as globally best, rather than best for a given denominator bound.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<string> simplifiedFractions(int n) {
        vector<string> result;
        for (int denom = 2; denom <= n; ++denom) {
            for (int numer = 1; numer < denom; ++numer) {
                if (gcd(numer, denom) == 1) {
                    result.push_back(to_string(numer) + "/" + to_string(denom));
                }
            }
        }
        return result;          
    }
};
