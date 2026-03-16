// Source: https://leetcode.com/problems/parsing-a-boolean-expression/   |   Difficulty: Hard
//
// Problem Description:
// A boolean expression is an expression that evaluates to either true or false. It can be in one of the following shapes:
//
//
// 	't' that evaluates to true.
// 	'f' that evaluates to false.
// 	'!(subExpr)' that evaluates to the logical NOT of the inner expression subExpr.
// 	'&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical AND of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
// 	'|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical OR of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
//
//
// Given a string expression that represents a boolean expression, return the evaluation of that expression.
//
// It is guaranteed that the given expression is valid and follows the given rules.
//
// Example:
// Input: expression = "&(|(f))"
// Output: false
// Explanation: 
// First, evaluate |(f) --> f. The expression is now "&(f)".
// Then, evaluate &(f) --> f. The expression is now "f".
// Finally, return false.
//
// Constraints:
// 1 <= expression.length <= 2 * 104
// 	expression[i] is one following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool parseBoolExpr(string expression) {
        stack<char> st;
        for (char c : expression) {
            if (c == ',') continue;
            if (c != ')') {
                st.push(c);
            } else {
                vector<bool> operands;
                while (!st.empty() && st.top() != '(') {
                    operands.push_back(st.top() == 't');
                    st.pop();
                }
                st.pop(); // pop '('
                char op = st.top();
                st.pop(); // pop operator
                bool result;
                if (op == '!') {
                    result = !operands[0];
                } else if (op == '&') {
                    result = true;
                    for (bool operand : operands) {
                        result &= operand;
                    }
                } else { // op == '|'
                    result = false;
                    for (bool operand : operands) {
                        result |= operand;
                    }
                }
                st.push(result ? 't' : 'f');
            }
        }
        return st.top() == 't';         
    }
};
