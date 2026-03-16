// Source: https://leetcode.com/problems/minimize-result-by-adding-parentheses-to-expression/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string expression of the form "<num1>+<num2>" where <num1> and <num2> represent positive integers.
//
// Add a pair of parentheses to expression such that after the addition of parentheses, expression is a valid mathematical expression and evaluates to the smallest possible value. The left parenthesis must be added to the left of '+' and the right parenthesis must be added to the right of '+'.
//
// Return expression after adding a pair of parentheses such that expression evaluates to the smallest possible value. If there are multiple answers that yield the same result, return any of them.
//
// The input has been generated such that the original value of expression, and the value of expression after adding any pair of parentheses that meets the requirements fits within a signed 32-bit integer.
//
// Example:
// Input: expression = "247+38"
// Output: "2(47+38)"
// Explanation: The expression evaluates to 2 * (47 + 38) = 2 * 85 = 170.
// Note that "2(4)7+38" is invalid because the right parenthesis must be to the right of the '+'.
// It can be shown that 170 is the smallest possible value.
//
// Constraints:
// 3 <= expression.length <= 10
// 	expression consists of digits from '1' to '9' and '+'.
// 	expression starts and ends with digits.
// 	expression contains exactly one '+'.
// 	The original value of expression, and the value of expression after adding any pair of parentheses that meets the requirements fits within a signed 32-bit integer.
//

char* minimizeResult(char* expression) {
    int plus_pos = 0;
    while (expression[plus_pos] != '+') {
        plus_pos++;
    }

    int len = strlen(expression);
    int min_value = INT_MAX;
    char* result = (char*)malloc((len + 3) * sizeof(char)); // +2 for parentheses, +1 for null terminator

    for (int i = 0; i < plus_pos; i++) {
        for (int j = plus_pos + 1; j <= len; j++) {
            int left_multiplier = (i == 0) ? 1 : atoi(strndup(expression, i));
            int right_multiplier = (j == len) ? 1 : atoi(strndup(expression + j, len - j));
            int left_operand = atoi(strndup(expression + i, plus_pos - i));
            int right_operand = atoi(strndup(expression + plus_pos + 1, j - plus_pos - 1));

            int current_value = left_multiplier * (left_operand + right_operand) * right_multiplier;

            if (current_value < min_value) {
                min_value = current_value;
                snprintf(result, len + 3, "%.*s(%.*s+%.*s)%.*s",
                         i, expression,
                         plus_pos - i, expression + i,
                         j - plus_pos - 1, expression + plus_pos + 1,
                         len - j, expression + j);
            }
        }
    }

    return result;      
}
