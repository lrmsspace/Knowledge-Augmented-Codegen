// Source: https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return true if it is possible to represent n as the sum of distinct powers of three. Otherwise, return false.
//
// An integer y is a power of three if there exists an integer x such that y == 3x.
//
// Example:
// Input: n = 12
// Output: true
// Explanation: 12 = 31 + 32
//
// Constraints:
// 1 <= n <= 107
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
    bool checkPowersOfThree(int n) {
        while (n > 0) {
            if (n % 3 == 2) {
                return false; // If the remainder is 2, it means we can't represent n as a sum of distinct powers of three
            }
            n /= 3; // Move to the next power of three
        }
        return true; // If we successfully reduced n to 0, it means we can represent n as a sum of distinct powers of three         
    }
};
