// Source: https://leetcode.com/problems/basic-calculator-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s which represents an expression, evaluate this expression and return its value. 
//
// The integer division should truncate toward zero.
//
// You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
//
// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().
//
// Example:
// Input: s = "3+2*2"
// Output: 7
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
// 	s represents a valid expression.
// 	All the integers in the expression are non-negative integers in the range [0, 231 - 1].
// 	The answer is guaranteed to fit in a 32-bit integer.
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
    public int calculate(String s) {
        int result = 0;
        int lastNumber = 0;
        char operation = '+';
        s = s.replaceAll(" ", "") + "+";

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            if (Character.isDigit(c)) {
                lastNumber = lastNumber * 10 + (c - '0');
            } else {
                switch (operation) {
                    case '+':
                        result += lastNumber;
                        break;
                    case '-':
                        result -= lastNumber;
                        break;
                    case '*':
                        result -= lastNumber; // Remove the last number added
                        result += lastNumber * lastNumber; // Add the product
                        break;
                    case '/':
                        result -= lastNumber; // Remove the last number added
                        result += lastNumber / lastNumber; // Add the quotient
                        break;
                }
                operation = c;
                lastNumber = 0;
            }
        }

        return result;          
    }
}
