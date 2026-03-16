// Source: https://leetcode.com/problems/basic-calculator/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.
//
// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().
//
// Example:
// Input: s = "1 + 1"
// Output: 2
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists of digits, '+', '-', '(', ')', and ' '.
// 	s represents a valid expression.
// 	'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
// 	'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
// 	There will be no two consecutive operators in the input.
// 	Every number and running calculation will fit in a signed 32-bit integer.
//

class Solution {
public:
    int calculate(string s) {
        int n = s.size();
        stack<int> nums;
        stack<char> ops;
        int num = 0;
        char sign = '+';
        
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            }
            if ((!isdigit(c) && c != ' ') || i == n - 1) {
                if (sign == '+') {
                    nums.push(num);
                } else if (sign == '-') {
                    nums.push(-num);
                } else if (sign == '*') {
                    int top = nums.top();
                    nums.pop();
                    nums.push(top * num);
                } else if (sign == '/') {
                    int top = nums.top();
                    nums.pop();
                    nums.push(top / num);
                }
                sign = c;
                num = 0;
            }
            if (c == '(') {
                ops.push(sign);
                nums.push(INT_MIN); // Marker for '('
                sign = '+';
            } else if (c == ')') {
                int subtotal = 0;
                while (nums.top() != INT_MIN) {
                    subtotal += nums.top();
                    nums.pop();
                }
                nums.pop(); // Remove marker
                char prevSign = ops.top();
                ops.pop();
                
                if (prevSign == '+') {
                    nums.push(subtotal);
                } else if (prevSign == '-') {
                    nums.push(-subtotal);
                }
            }
        }
        
        int result = 0;
        while (!nums.empty()) {
            result += nums.top();
            nums.pop();
        }
        
        return result;          
    }
};
