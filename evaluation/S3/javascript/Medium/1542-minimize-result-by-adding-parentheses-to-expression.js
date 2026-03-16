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
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} expression
 * @return {string}
 */
var minimizeResult = function(expression) {
    const [num1, num2] = expression.split('+');
    let minValue = Infinity;
    let resultExpression = '';
    for (let i = 0; i < num1.length; i++) {
        for (let j = 1; j <= num2.length; j++) {
            const leftPart = num1.slice(0, i);
            const middlePart = num1.slice(i) + '+' + num2.slice(0, j);
            const rightPart = num2.slice(j);
            const value = (leftPart ? parseInt(leftPart) : 1) * (parseInt(middlePart)) * (rightPart ? parseInt(rightPart) : 1);
            if (value < minValue) {
                minValue = value;
                resultExpression = `${leftPart ? leftPart : ''}(${middlePart})${rightPart ? rightPart : ''}`;
            }
        }
    }
    return resultExpression;
};
