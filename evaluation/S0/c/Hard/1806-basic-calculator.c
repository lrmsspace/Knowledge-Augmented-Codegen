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

int calculate(char* s) {
    int stack[10000];
    int top = -1;
    int sign = 1; /* current sign */
    int result = 0;
    int number = 0;

    for (char *p = s; *p; ++p) {
        if (*p >= '0' && *p <= '9') {
            number = number * 10 + (*p - '0');
        } else if (*p == '+') {
            result += sign * number;
            number = 0;
            sign = 1;
        } else if (*p == '-') {
            result += sign * number;
            number = 0;
            sign = -1;
        } else if (*p == '(') {
            /* push current result and sign onto stack */
            stack[++top] = result;
            stack[++top] = sign;
            /* reset for new sub-expression */
            result = 0;
            sign = 1;
        } else if (*p == ')') {
            result += sign * number;
            number = 0;
            /* pop sign and previous result */
            int prevSign = stack[top--];
            int prevResult = stack[top--];
            result = prevResult + prevSign * result;
        }
        /* ignore spaces */
    }
    result += sign * number; /* add last number */
    return result;      
}
