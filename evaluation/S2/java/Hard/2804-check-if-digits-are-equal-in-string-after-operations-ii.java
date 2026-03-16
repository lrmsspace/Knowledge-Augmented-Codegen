// Source: https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of digits. Perform the following operation repeatedly until the string has exactly two digits:
//
//
// 	For each pair of consecutive digits in s, starting from the first digit, calculate a new digit as the sum of the two digits modulo 10.
// 	Replace s with the sequence of newly calculated digits, maintaining the order in which they are computed.
//
//
// Return true if the final two digits in s are the same; otherwise, return false.
//
// Example:
// Input: s = "3902"
//
// Output: true
//
// Explanation:
//
//
// 	Initially, s = "3902"
// 	First operation:
// 	
// 		(s[0] + s[1]) % 10 = (3 + 9) % 10 = 2
// 		(s[1] + s[2]) % 10 = (9 + 0) % 10 = 9
// 		(s[2] + s[3]) % 10 = (0 + 2) % 10 = 2
// 		s becomes "292"
// 	
// 	
// 	Second operation:
// 	
// 		(s[0] + s[1]) % 10 = (2 + 9) % 10 = 1
// 		(s[1] + s[2]) % 10 = (9 + 2) % 10 = 1
// 		s becomes "11"
// 	
// 	
// 	Since the digits in "11" are the same, the output is true.
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of only digits.
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
    public boolean hasSameDigits(String s) {
        while (s.length() > 2) {
            StringBuilder newS = new StringBuilder();
            for (int i = 0; i < s.length() - 1; i++) {
                int sum = (s.charAt(i) - '0') + (s.charAt(i + 1) - '0');
                newS.append(sum % 10);
            }
            s = newS.toString();
        }
        return s.charAt(0) == s.charAt(1);          
    }
}
