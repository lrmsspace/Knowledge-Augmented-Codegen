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

bool parseBoolExpr(char* expression) {
    int len = strlen(expression);
    char stack[len];
    int top = -1;

    for (int i = 0; i < len; ++i) {
        char c = expression[i];
        if (c == ',') {
            continue;
        } else if (c != ')') {
            stack[++top] = c;
        } else {
            // Evaluate the expression inside the parentheses
            char op = stack[top--]; // operator before '('
            int trueCount = 0, falseCount = 0;

            while (top >= 0 && stack[top] != '(') {
                char val = stack[top--];
                if (val == 't') {
                    trueCount++;
                } else if (val == 'f') {
                    falseCount++;
                }
            }
            top--; // pop '('

            char result;
            if (op == '!') {
                result = (falseCount == 1) ? 't' : 'f';
            } else if (op == '&') {
                result = (falseCount > 0) ? 'f' : 't';
            } else if (op == '|') {
                result = (trueCount > 0) ? 't' : 'f';
            }
            stack[++top] = result;
        }
    }

    return stack[top] == 't';       
}
