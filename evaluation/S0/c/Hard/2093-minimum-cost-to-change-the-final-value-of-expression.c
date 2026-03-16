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

int minOperationsToFlip(char* expression) {
    int n = strlen(expression);
    /* stack to hold pairs of (cost to make 0, cost to make 1) */
    int *stack = (int*)malloc(n * 2 * sizeof(int));
    int sp = 0; /* stack pointer */

    for (int i = 0; i < n; ++i) {
        char c = expression[i];
        if (c == '0') {
            stack[sp++] = 0; /* cost to make 0 */
            stack[sp++] = 1; /* cost to make 1 */
        } else if (c == '1') {
            stack[sp++] = 1; /* cost to make 0 */
            stack[sp++] = 0; /* cost to make 1 */
        } else if (c == '&' || c == '|') {
            stack[sp++] = c; /* push operator as is */
        } else if (c == '(') {
            stack[sp++] = c; /* push '(' as is */
        } else if (c == ')') {
            /* evaluate until '(' */
            int vals[2][2]; /* vals[i][0]: cost to make 0, vals[i][1]: cost to make 1 */
            int valCount = 0;
            while (sp > 0) {
                int top = stack[--sp];
                if (top == '(') break;
                if (top == '&' || top == '|') {
                    char op = top;
                    int right1 = stack[--sp], right0 = stack[--sp];
                    int left1 = stack[--sp], left0 = stack[--sp];
                    int res0, res1;
                    if (op == '&') {
                        res0 = fmin(left0 + right0, fmin(left0 + right1, left1 + right0));
                        res1 = left1 + right1;
                    } else { /* op == '|' */
                        res0 = left0 + right0;
                        res1 = fmin(left1 + right1, fmin(left1 + right0, left0 + right1));
                    }
                    stack[sp++] = res0;
                    stack[sp++] = res1;
                } else {
                    vals[valCount][1] = top;     /* cost to make 1 */
                    vals[valCount][0] = stack[--sp]; /* cost to make 0 */
                    valCount++;
                }
            }
            /* push back the evaluated result */
            stack[sp++] = vals[0][0];
            stack[sp++] = vals[0][1];
        }
    }
    int final0 = stack[0];
    int final1 = stack[1];
    free(stack);
    return fmin(final0, final1);
}
