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
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
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
        int totalActive = count(s.begin(), s.end(), '1');
        if (totalActive == n) return n; // All sections are active, no trade needed.

        int maxActive = totalActive;
        int leftOnes = 0; // Count of '1's in the left block.
        int rightOnes = totalActive; // Count of '1's in the right block (initially all).

        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                // If we convert this block of '1's to '0's, we lose leftOnes and gain rightOnes.
                maxActive = max(maxActive, totalActive - leftOnes + rightOnes);
                leftOnes++;
                rightOnes--;
            } else {
                // If we convert this block of '0's to '1's, we gain 1 active section.
                maxActive = max(maxActive, totalActive - leftOnes + rightOnes + 1);
            }
        }

        return maxActive;           
    }
};
