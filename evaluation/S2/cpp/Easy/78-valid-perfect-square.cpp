// Source: https://leetcode.com/problems/valid-perfect-square/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num, return true if num is a perfect square or false otherwise.
//
// A perfect square is an integer that is the square of an integer. In other words, it is the product of some integer with itself.
//
// You must not use any built-in library function, such as sqrt.
//
// Example:
// Input: num = 16
// Output: true
// Explanation: We return true because 4 * 4 = 16 and 4 is an integer.
//
// Constraints:
// 1 <= num <= 231 - 1
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
    bool isPerfectSquare(int num) {
        if (num < 2) {
            return true;
        }

        long left = 2, right = num / 2;

        while (left <= right) {
            long mid = left + (right - left) / 2;
            long square = mid * mid;

            if (square == num) {
                return true;
            } else if (square < num) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return false;           
    }
};
