// Source: https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer num. You know that Bob will sneakily remap one of the 10 possible digits (0 to 9) to another digit.
//
// Return the difference between the maximum and minimum values Bob can make by remapping exactly one digit in num.
//
// 	The resulting number after remapping can contain leading zeroes.
//
// Example:
// Input: num = 11891
// Output: 99009
// Explanation: 
// To achieve the maximum value, Bob can remap the digit 1 to the digit 9 to yield 99899.
// To achieve the minimum value, Bob can remap the digit 1 to the digit 0, yielding 890.
// The difference between these two numbers is 99009.
//
// Constraints:
// 1 <= num <= 108
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minMaxDifference(int num) {
        String numStr = Integer.toString(num);
        
        // Calculate maximum value
        char maxDigit = '0';
        for (char digit : numStr.toCharArray()) {
            if (digit > maxDigit) {
                maxDigit = digit;
            }
        }
        String maxStr = numStr.replace(maxDigit, '9');
        int maxValue = Integer.parseInt(maxStr);
        
        // Calculate minimum value
        char minDigit = '9';
        for (char digit : numStr.toCharArray()) {
            if (digit < minDigit && digit != '0') {
                minDigit = digit;
            }
        }
        String minStr = numStr.replace(minDigit, '0');
        int minValue = Integer.parseInt(minStr);
        
        return maxValue - minValue;         
    }
}
