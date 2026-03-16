// Source: https://leetcode.com/problems/number-complement/   |   Difficulty: Easy
//
// Problem Description:
// The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.
//
//
// 	For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
//
//
// Given an integer num, return its complement.
//
// Example:
// Input: num = 5
// Output: 2
// Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
//
// Constraints:
// 1 <= num < 231
//
//
//  
// Note: This question is the same as 1009: https://leetcode.com/problems/complement-of-base-10-integer/
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
    int findComplement(int num) {
        int mask = 1;
        while (mask < num) {
            mask = (mask << 1) | 1; // Shift left and set the least significant bit to 1
        }
        return num ^ mask; // XOR with the mask to get the complement           
    }
};
