// Source: https://leetcode.com/problems/maximum-product-of-two-digits/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer n.
//
// Return the maximum product of any two digits in n.
//
// Note: You may use the same digit twice if it appears more than once in n.
//
// Example:
// Input: n = 31
//
// Output: 3
//
// Explanation:
//
//
// 	The digits of n are [3, 1].
// 	The possible products of any two digits are: 3 * 1 = 3.
// 	The maximum product is 3.
//
// Constraints:
// 10 <= n <= 109
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
    public int maxProduct(int n) {
        int maxDigit = 0;
        int secondMaxDigit = 0;

        while (n > 0) {
            int digit = n % 10;

            if (digit > maxDigit) {
                secondMaxDigit = maxDigit;
                maxDigit = digit;
            } else if (digit > secondMaxDigit) {
                secondMaxDigit = digit;
            }

            n /= 10;
        }

        return maxDigit * secondMaxDigit;           
    }
}
