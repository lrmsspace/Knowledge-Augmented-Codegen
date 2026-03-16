// Source: https://leetcode.com/problems/gray-code/   |   Difficulty: Medium
//
// Problem Description:
// An n-bit gray code sequence is a sequence of 2n integers where:
//
//
// 	Every integer is in the inclusive range [0, 2n - 1],
// 	The first integer is 0,
// 	An integer appears no more than once in the sequence,
// 	The binary representation of every pair of adjacent integers differs by exactly one bit, and
// 	The binary representation of the first and last integers differs by exactly one bit.
//
//
// Given an integer n, return any valid n-bit gray code sequence.
//
// Example:
// Input: n = 2
// Output: [0,1,3,2]
// Explanation:
// The binary representation of [0,1,3,2] is [00,01,11,10].
// - 00 and 01 differ by one bit
// - 01 and 11 differ by one bit
// - 11 and 10 differ by one bit
// - 10 and 00 differ by one bit
// [0,2,3,1] is also a valid gray code sequence, whose binary representation is [00,10,11,01].
// - 00 and 10 differ by one bit
// - 10 and 11 differ by one bit
// - 11 and 01 differ by one bit
// - 01 and 00 differ by one bit
//
// Constraints:
// 1 <= n <= 16
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
    public List<Integer> grayCode(int n) {
        List<Integer> result = new ArrayList<>();
        int totalNumbers = 1 << n; // 2^n

        for (int i = 0; i < totalNumbers; i++) {
            int grayCodeNumber = i ^ (i >> 1);
            result.add(grayCodeNumber);
        }

        return result;          
    }
}
