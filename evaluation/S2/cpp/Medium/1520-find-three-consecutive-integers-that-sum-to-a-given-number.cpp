// Source: https://leetcode.com/problems/find-three-consecutive-integers-that-sum-to-a-given-number/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer num, return three consecutive integers (as a sorted array) that sum to num. If num cannot be expressed as the sum of three consecutive integers, return an empty array.
//
// Example:
// Input: num = 33
// Output: [10,11,12]
// Explanation: 33 can be expressed as 10 + 11 + 12 = 33.
// 10, 11, 12 are 3 consecutive integers, so we return [10, 11, 12].
//
// Constraints:
// 0 <= num <= 1015
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
    vector<long long> sumOfThree(long long num) {
        // The sum of three consecutive integers starting from x is:
        // x + (x + 1) + (x + 2) = 3x + 3 = 3(x + 1)
        // Therefore, num must be divisible by 3 for there to be a solution.
        if (num % 3 != 0) {
            return {};
        }

        long long x = num / 3 - 1; // This gives us the middle integer
        return {x, x + 1, x + 2}; // Return the three consecutive integers          
    }
};
