// Source: https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two positive integers n and k, the binary string Sn is formed as follows:
//
//
// 	S1 = "0"
// 	Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
//
//
// Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).
//
// For example, the first four strings in the above sequence are:
//
//
// 	S1 = "0"
// 	S2 = "011"
// 	S3 = "0111001"
// 	S4 = "011100110110001"
//
//
// Return the kth bit in Sn. It is guaranteed that k is valid for the given n.
//
// Example:
// Input: n = 3, k = 1
// Output: "0"
// Explanation: S3 is "0111001".
// The 1st bit is "0".
//
// Constraints:
// 1 <= n <= 20
// 	1 <= k <= 2n - 1
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
    public char findKthBit(int n, int k) {
        if (n == 1) {
            return '0';
        }

        int mid = (1 << (n - 1)) - 1; // Length of Sn-1
        if (k == mid + 1) {
            return '1';
        } else if (k <= mid) {
            return findKthBit(n - 1, k);
        } else {
            char bit = findKthBit(n - 1, mid - (k - mid - 1) + 1);
            return bit == '0' ? '1' : '0'; // Invert the bit
        }           
    }
}
