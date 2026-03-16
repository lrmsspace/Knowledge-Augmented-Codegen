// Source: https://leetcode.com/problems/check-balanced-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string num consisting of only digits. A string of digits is called balanced if the sum of the digits at even indices is equal to the sum of digits at odd indices.
//
// Return true if num is balanced, otherwise return false.
//
// Example:
// Input: num = "1234"
//
// Output: false
//
// Explanation:
//
//
// 	The sum of digits at even indices is 1 + 3 == 4, and the sum of digits at odd indices is 2 + 4 == 6.
// 	Since 4 is not equal to 6, num is not balanced.
//
// Constraints:
// 2 <= num.length <= 100
// 	num consists of digits only
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
    public boolean isBalanced(String num) {
        int evenSum = 0;
        int oddSum = 0;

        for (int i = 0; i < num.length(); i++) {
            int digit = num.charAt(i) - '0'; // Convert char to int

            if (i % 2 == 0) {
                evenSum += digit; // Even index
            } else {
                oddSum += digit; // Odd index
            }
        }

        return evenSum == oddSum; // Check if sums are equal            
    }
}
