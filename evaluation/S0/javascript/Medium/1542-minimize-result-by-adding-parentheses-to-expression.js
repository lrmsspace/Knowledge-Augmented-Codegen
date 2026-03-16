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

/**
 * @param {string} expression
 * @return {string}
 */
var minimizeResult = function(expression) {
    const plusIndex = expression.indexOf('+');
    let minValue = Infinity;
    let result = '';
    const leftPart = expression.substring(0, plusIndex);
    const rightPart = expression.substring(plusIndex + 1);

    for (let i = 0; i < leftPart.length; i++) {
        for (let j = 1; j <= rightPart.length; j++) {
            const leftMultiplier = i === 0 ? 1 : parseInt(leftPart.substring(0, i));
            const leftNumber = parseInt(leftPart.substring(i));
            const rightNumber = parseInt(rightPart.substring(0, j));
            const rightMultiplier = j === rightPart.length ? 1 : parseInt(rightPart.substring(j));
            const value = leftMultiplier * (leftNumber + rightNumber) * rightMultiplier;
            if (value < minValue) {
                minValue = value;
                result = leftPart.substring(0, i) + '(' + leftPart.substring(i) + '+' + rightPart.substring(0, j) + ')' + rightPart.substring(j);
            }
        }
    }
    return result;
};