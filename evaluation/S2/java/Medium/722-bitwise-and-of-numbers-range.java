// Source: https://leetcode.com/problems/bitwise-and-of-numbers-range/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers left and right that represent the range [left, right], return the bitwise AND of all numbers in this range, inclusive.
//
// Example:
// Input: left = 5, right = 7
// Output: 4
//
// Constraints:
// 0 <= left <= right <= 231 - 1
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int rangeBitwiseAnd(int left, int right) {
        int shift = 0;
        // Find the common prefix of left and right
        while (left != right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }
        // Shift back to get the result
        return left << shift;           
    }
}
