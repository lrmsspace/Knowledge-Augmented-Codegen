// Source: https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/   |   Difficulty: Medium
//
// Problem Description:
// Given the binary representation of an integer as a string s, return the number of steps to reduce it to 1 under the following rules:
//
//
// 	
// 	If the current number is even, you have to divide it by 2.
// 	
// 	
// 	If the current number is odd, you have to add 1 to it.
// 	
//
//
// It is guaranteed that you can always reach one for all test cases.
//
// Example:
// Input: s = "1101"
// Output: 6
// Explanation: "1101" corressponds to number 13 in their decimal representation.
// Step 1) 13 is odd, add 1 and obtain 14. 
// Step 2) 14 is even, divide by 2 and obtain 7.
// Step 3) 7 is odd, add 1 and obtain 8.
// Step 4) 8 is even, divide by 2 and obtain 4.  
// Step 5) 4 is even, divide by 2 and obtain 2. 
// Step 6) 2 is even, divide by 2 and obtain 1.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of characters '0' or '1'
// 	s[0] == '1'
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Gray code (number, simulation)
//   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
//   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
//   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
//   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
//   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numSteps(string s) {
        int steps = 0;
        int carry = 0;
        for (int i = s.size() - 1; i > 0; --i) {
            if ((s[i] - '0') + carry == 1) {
                carry = 1;
                steps += 2; // odd: add 1 (1 step) and then divide by 2 (1 step)
            } else {
                steps += 1; // even: just divide by 2 (1 step)
            }
        }
        return steps + carry; // add final step if there's a carry left         
    }
};
