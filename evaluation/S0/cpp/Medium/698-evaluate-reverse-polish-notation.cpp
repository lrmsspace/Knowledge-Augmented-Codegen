// Source: https://leetcode.com/problems/evaluate-reverse-polish-notation/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.
//
// Evaluate the expression. Return an integer that represents the value of the expression.
//
// Note that:
//
//
// 	The valid operators are '+', '-', '*', and '/'.
// 	Each operand may be an integer or another expression.
// 	The division between two integers always truncates toward zero.
// 	There will not be any division by zero.
// 	The input represents a valid arithmetic expression in a reverse polish notation.
// 	The answer and all the intermediate calculations can be represented in a 32-bit integer.
//
// Example:
// Input: tokens = ["2","1","+","3","*"]
// Output: 9
// Explanation: ((2 + 1) * 3) = 9
//
// Constraints:
// 1 <= tokens.length <= 104
// 	tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].
//

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for (const string& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = stk.top(); stk.pop();
                int a = stk.top(); stk.pop();
                int result;
                if (token == "+") {
                    result = a + b;
                } else if (token == "-") {
                    result = a - b;
                } else if (token == "*") {
                    result = a * b;
                } else { // token == "/"
                    result = a / b;
                }
                stk.push(result);
            } else {
                stk.push(stoi(token));
            }
        }
        return stk.top();           
    }
};
