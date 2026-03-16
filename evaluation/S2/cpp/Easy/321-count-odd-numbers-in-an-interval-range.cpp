// Source: https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/   |   Difficulty: Easy
//
// Problem Description:
// Given two non-negative integers low and high. Return the count of odd numbers between low and high (inclusive).
//
// Example:
// Input: low = 3, high = 7
// Output: 3
// Explanation: The odd numbers between 3 and 7 are [3,5,7].
//
// Constraints:
// 0 <= low <= high <= 10^9
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countOdds(int low, int high) {
        // Count of odd numbers up to high
        int countHigh = (high + 1) / 2;
        // Count of odd numbers up to low - 1
        int countLow = low / 2;
        
        return countHigh - countLow;            
    }
};
