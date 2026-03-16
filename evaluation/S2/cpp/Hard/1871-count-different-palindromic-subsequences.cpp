// Source: https://leetcode.com/problems/count-different-palindromic-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, return the number of different non-empty palindromic subsequences in s. Since the answer may be very large, return it modulo 109 + 7.
//
// A subsequence of a string is obtained by deleting zero or more characters from the string.
//
// A sequence is palindromic if it is equal to the sequence reversed.
//
// Two sequences a1, a2, ... and b1, b2, ... are different if there is some i for which ai != bi.
//
// Example:
// Input: s = "bccb"
// Output: 6
// Explanation: The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
// Note that 'bcb' is counted only once, even though it occurs twice.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either 'a', 'b', 'c', or 'd'.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countPalindromicSubsequences(string s) {
        const int mod = 1e9 + 7;
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int i = n - 1; i >= 0; --i) {
            dp[i][i] = 1; // Single character is a palindrome
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    int low = i + 1, high = j - 1;
                    while (low <= high && s[low] != s[i]) low++;
                    while (low <= high && s[high] != s[j]) high--;
                    
                    if (low > high) {
                        dp[i][j] = dp[i + 1][j - 1] * 2 + 2; // No same character inside
                    } else if (low == high) {
                        dp[i][j] = dp[i + 1][j - 1] * 2 + 1; // One same character inside
                    } else {
                        dp[i][j] = dp[i + 1][j - 1] * 2 - dp[low + 1][high - 1]; // More than one same character inside
                    }
                } else {
                    dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1]; // Different characters
                }
                dp[i][j] = (dp[i][j] % mod + mod) % mod; // Ensure non-negative modulo
            }
        }
        
        return dp[0][n - 1];            
    }
};
