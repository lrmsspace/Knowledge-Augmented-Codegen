// Source: https://leetcode.com/problems/minimum-cost-to-change-the-final-value-of-expression/   |   Difficulty: Hard
//
// Problem Description:
// You are given a valid boolean expression as a string expression consisting of the characters '1','0','&' (bitwise AND operator),'|' (bitwise OR operator),'(', and ')'.
//
//
// 	For example, "()1|1" and "(1)&()" are not valid while "1", "(((1))|(0))", and "1|(0&(1))" are valid expressions.
//
//
// Return the minimum cost to change the final value of the expression.
//
//
// 	For example, if expression = "1|1|(0&0)&1", its value is 1|1|(0&0)&1 = 1|1|0&1 = 1|0&1 = 1&1 = 1. We want to apply operations so that the new expression evaluates to 0.
//
//
// The cost of changing the final value of an expression is the number of operations performed on the expression. The types of operations are described as follows:
//
//
// 	Turn a '1' into a '0'.
// 	Turn a '0' into a '1'.
// 	Turn a '&' into a '|'.
// 	Turn a '|' into a '&'.
//
//
// Note: '&' does not take precedence over '|' in the order of calculation. Evaluate parentheses first, then in left-to-right order.
//
// Example:
// Input: expression = "1&(0|1)"
// Output: 1
// Explanation: We can turn "1&(0|1)" into "1&(0&1)" by changing the '|' to a '&' using 1 operation.
// The new expression evaluates to 0.
//
// Constraints:
// 1 <= expression.length <= 105
// 	expression only contains '1','0','&','|','(', and ')'
// 	All parentheses are properly matched.
// 	There will be no empty parentheses (i.e: "()" is not a substring of expression).
//

class Solution {
public:
    int minOperationsToFlip(string expression) {
        stack<pair<int, int>> stk; // pair<value, cost>
        stack<char> ops;
        
        auto applyOp = [&](char op) {
            auto right = stk.top(); stk.pop();
            auto left = stk.top(); stk.pop();
            int val, cost;
            if (op == '&') {
                val = left.first & right.first;
                if (val == 1) {
                    cost = min(left.second, right.second);
                } else {
                    cost = min({left.second + (right.first == 0 ? 0 : 1),
                                right.second + (left.first == 0 ? 0 : 1)});
                }
            } else { // op == '|'
                val = left.first | right.first;
                if (val == 0) {
                    cost = min(left.second, right.second);
                } else {
                    cost = min({left.second + (right.first == 1 ? 0 : 1),
                                right.second + (left.first == 1 ? 0 : 1)});
                }
            }
            stk.push({val, cost});
        };
        
        for (char ch : expression) {
            if (ch == '0' || ch == '1') {
                stk.push({ch - '0', 1});
            } else if (ch == '&' || ch == '|') {
                while (!ops.empty() && ops.top() != '(') {
                    applyOp(ops.top());
                    ops.pop();
                }
                ops.push(ch);
            } else if (ch == '(') {
                ops.push(ch);
            } else if (ch == ')') {
                while (ops.top() != '(') {
                    applyOp(ops.top());
                    ops.pop();
                }
                ops.pop(); // pop '('
            }
        }
        
        while (!ops.empty()) {
            applyOp(ops.top());
            ops.pop();
        }
        
        return stk.top().second;
    }
};
