// Source: https://leetcode.com/problems/largest-palindromic-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string num consisting of digits only.
//
// Return the largest palindromic integer (in the form of a string) that can be formed using digits taken from num. It should not contain leading zeroes.
//
// Example:
// Input: num = "444947137"
// Output: "7449447"
// Explanation: 
// Use the digits "4449477" from "444947137" to form the palindromic integer "7449447".
// It can be shown that "7449447" is the largest palindromic integer that can be formed.
//
// Constraints:
// 1 <= num.length <= 105
// 	num consists of digits.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String largestPalindromic(String num) {
        int[] count = new int[10];
        for (char c : num.toCharArray()) {
            count[c - '0']++;
        }

        StringBuilder leftHalf = new StringBuilder();
        for (int digit = 9; digit >= 0; digit--) {
            while (count[digit] >= 2) {
                if (digit != 0 || leftHalf.length() > 0) {
                    leftHalf.append(digit);
                    count[digit] -= 2;
                } else {
                    break;
                }
            }
        }

        StringBuilder rightHalf = new StringBuilder(leftHalf).reverse();

        String middleDigit = "";
        for (int digit = 9; digit >= 0; digit--) {
            if (count[digit] > 0) {
                middleDigit = String.valueOf(digit);
                break;
            }
        }

        String result = leftHalf.toString() + middleDigit + rightHalf.toString();
        return result.isEmpty() ? "0" : result;         
    }
}
