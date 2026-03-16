// Source: https://leetcode.com/problems/check-if-number-has-equal-digit-count-and-digit-value/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed string num of length n consisting of digits.
//
// Return true if for every index i in the range 0 <= i < n, the digit i occurs num[i] times in num, otherwise return false.
//
// Example:
// Input: num = "1210"
// Output: true
// Explanation:
// num[0] = '1'. The digit 0 occurs once in num.
// num[1] = '2'. The digit 1 occurs twice in num.
// num[2] = '1'. The digit 2 occurs once in num.
// num[3] = '0'. The digit 3 occurs zero times in num.
// The condition holds true for every index in "1210", so return true.
//
// Constraints:
// n == num.length
// 	1 <= n <= 10
// 	num consists of digits.
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
    public boolean digitCount(String num) {
        int[] count = new int[10];
        for (char c : num.toCharArray()) {
            count[c - '0']++;
        }
        for (int i = 0; i < num.length(); i++) {
            if (count[i] != num.charAt(i) - '0') {
                return false;
            }
        }
        return true;            
    }
}
