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

class Solution {
public:
    bool parseBoolExpr(string expression) {
        stack<char> ops;
        stack<bool> vals;
        
        for (char c : expression) {
            if (c == ',') continue;
            else if (c == 't' || c == 'f') {
                vals.push(c == 't');
            } else if (c == '&' || c == '|' || c == '!') {
                ops.push(c);
            } else if (c == '(') {
                // do nothing
            } else if (c == ')') {
                char op = ops.top(); ops.pop();
                
                if (op == '!') {
                    bool val = vals.top(); vals.pop();
                    vals.push(!val);
                } else {
                    vector<bool> arguments;
                    while (!vals.empty() && (ops.empty() || ops.top() != op)) {
                        arguments.push_back(vals.top());
                        vals.pop();
                    }
                    
                    bool result;
                    if (op == '&') {
                        result = true;
                        for (bool arg : arguments) {
                            result = result && arg;
                        }
                    } else { // op == '|'
                        result = false;
                        for (bool arg : arguments) {
                            result = result || arg;
                        }
                    }
                    vals.push(result);
                }
            }
        }
        
        return vals.top();          
    }
};
