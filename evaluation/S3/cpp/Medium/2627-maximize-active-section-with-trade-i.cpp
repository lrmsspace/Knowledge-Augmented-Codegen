// Source: https://leetcode.com/problems/maximize-active-section-with-trade-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s of length n, where:
//
//
// 	'1' represents an active section.
// 	'0' represents an inactive section.
//
//
// You can perform at most one trade to maximize the number of active sections in s. In a trade, you:
//
//
// 	Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
// 	Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
//
//
// Return the maximum number of active sections in s after making the optimal trade.
//
// Note: Treat s as if it is augmented with a '1' at both ends, forming t = '1' + s + '1'. The augmented '1's do not contribute to the final count.
//
// Example:
// Input: s = "01"
//
// Output: 1
//
// Explanation:
//
// Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.
//
// Constraints:
// 1 <= n == s.length <= 105
// 	s[i] is either '0' or '1'
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Fibonacci Numbers (number, greedy, enumeration)
//   • When to use: When you need a unique, non-ambiguous binary representation of positive integers based on Fibonacci numbers, ensuring no two consecutive Fibonacci numbers are used in the sum.
//   • Idea: This algorithm encodes a positive integer into a unique binary string by greedily finding its Zeckendorf representation (sum of non-consecutive Fibonacci numbers). The encoding process typically involves iterating through Fibonacci numbers, resulting in a logarithmic time complexity relative to the input number's magnitude.
//   • Invariants: The remaining value 'n' to be encoded is always non-negative.; The partial binary code constructed so far represents a valid Zeckendorf sum of non-consecutive Fibonacci numbers.
//   • Tips: Precompute Fibonacci numbers up to a certain limit to optimize lookups.; Always start with the largest Fibonacci number less than or equal to the target value.
//   • Pitfalls: Incorrectly handling the base cases for small numbers like 1 or 2.; Forgetting to append the mandatory final '1' bit to the codeword.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        int left = 0, right = 0;
        int maxActive = 0;

        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                left++;
            } else {
                right++;
            }
            maxActive = max(maxActive, left + right);
        }

        return maxActive;           
    }
};
