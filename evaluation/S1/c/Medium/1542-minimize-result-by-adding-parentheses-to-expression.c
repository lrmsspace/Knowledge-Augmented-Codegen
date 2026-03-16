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
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* minimizeResult(char* expression) {
    int plus_pos = 0;
    while (expression[plus_pos] != '+') {
        plus_pos++;
    }

    int len = 0;
    while (expression[len] != '\0') {
        len++;
    }

    int min_value = 2147483647; // Max 32-bit signed integer
    int best_left = 0;
    int best_right = 0;

    for (int left = 0; left < plus_pos; left++) {
        for (int right = plus_pos + 1; right < len; right++) {
            int left_multiplier = (left == 0) ? 1 : atoi((char[]){expression[0], '\0'}) * 10 + atoi((char[]){expression[1], '\0'});
            for (int i = 1; i < left; i++) {
                left_multiplier = left_multiplier * 10 + (expression[i] - '0');
            }

            int right_multiplier = (right == len - 1) ? 1 : atoi((char[]){expression[right + 1], '\0'}) * 10 + atoi((char[]){expression[right + 2], '\0'});
            for (int i = right + 2; i < len; i++) {
                right_multiplier = right_multiplier * 10 + (expression[i] - '0');
            }

            int num1 = 0;
            for (int i = left; i < plus_pos; i++) {
                num1 = num1 * 10 + (expression[i] - '0');
            }

            int num2 = 0;
            for (int i = plus_pos + 1; i <= right; i++) {
                num2 = num2 * 10 + (expression[i] - '0');
            }

            int current_value = left_multiplier * (num1 + num2) * right_multiplier;

            if (current_value < min_value) {
                min_value = current_value;
                best_left = left;
                best_right = right;
            }
        }
    }

    char* result = (char*)malloc((len + 3) * sizeof(char)); // +2 for parentheses, +1 for null terminator
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (i == best_left) {
            result[index++] = '(';
        }
        result[index++] = expression[i];
        if (i == best_right) {
            result[index++] = ')';
        }
    }
    result[index] = '\0';
    return result;
}
