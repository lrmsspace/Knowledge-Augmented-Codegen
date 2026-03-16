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

class Solution {
public:
    int calculate(string s) {
        long long result = 0;
        long long lastNumber = 0;
        long long currentNumber = 0;
        char operation = '+';
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            char currentChar = s[i];

            if (isdigit(currentChar)) {
                currentNumber = currentNumber * 10 + (currentChar - '0');
            }

            if ((!isdigit(currentChar) && !isspace(currentChar)) || i == n - 1) {
                if (operation == '+' || operation == '-') {
                    result += lastNumber;
                    lastNumber = (operation == '+') ? currentNumber : -currentNumber;
                } else if (operation == '*') {
                    lastNumber = lastNumber * currentNumber;
                } else if (operation == '/') {
                    lastNumber = lastNumber / currentNumber;
                }
                operation = currentChar;
                currentNumber = 0;
            }
        }

        result += lastNumber;
        return result;          
    }
};
