// Source: https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers num1 and num2.
//
// In one operation, you can choose integer i in the range [0, 60] and subtract 2i + num2 from num1.
//
// Return the integer denoting the minimum number of operations needed to make num1 equal to 0.
//
// If it is impossible to make num1 equal to 0, return -1.
//
// Example:
// Input: num1 = 3, num2 = -2
// Output: 3
// Explanation: We can make 3 equal to 0 with the following operations:
// - We choose i = 2 and subtract 22 + (-2) from 3, 3 - (4 + (-2)) = 1.
// - We choose i = 2 and subtract 22 + (-2) from 1, 1 - (4 + (-2)) = -1.
// - We choose i = 0 and subtract 20 + (-2) from -1, (-1) - (1 + (-2)) = 0.
// It can be proven, that 3 is the minimum number of operations that we need to perform.
//
// Constraints:
// 1 <= num1 <= 109
//  -109 <= num2 <= 109
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
    int makeTheIntegerZero(int num1, int num2) {
        int operations = 0;
        while (num1 > 0) {
            // Count the number of set bits in num1
            int setBits = __builtin_popcount(num1);
            // If the number of set bits is greater than the remaining num1, it's impossible
            if (setBits > num1) {
                return -1;
            }
            // Subtract num2 from num1
            num1 -= num2;
            operations++;
        }
        // If num1 is exactly zero, return the number of operations
        return num1 == 0 ? operations : -1;         
    }
};
