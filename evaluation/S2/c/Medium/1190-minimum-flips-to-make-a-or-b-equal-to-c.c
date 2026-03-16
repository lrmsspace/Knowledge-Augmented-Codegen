// Source: https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/   |   Difficulty: Medium
//
// Problem Description:
// Given 3 positives numbers a, b and c. Return the minimum flips required in some bits of a and b to make ( a OR b == c ). (bitwise OR operation).
// Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary representation.
//
// Example:
// Input: a = 2, b = 6, c = 5
// Output: 3
// Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)
//
// Constraints:
// 1 <= a <= 10^9
// 	1 <= b <= 10^9
// 	1 <= c <= 10^9
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.



int minFlips(int a, int b, int c){
    int flips = 0;
    while (a > 0 || b > 0 || c > 0) {
        int bitA = a & 1;
        int bitB = b & 1;
        int bitC = c & 1;

        if ((bitA | bitB) != bitC) {
            if (bitC == 0) {
                flips += bitA + bitB; // Flip both bits if they are 1
            } else {
                flips += 1; // Flip one bit to make it 1
            }
        }

        a >>= 1;
        b >>= 1;
        c >>= 1;
    }
    return flips;
}
