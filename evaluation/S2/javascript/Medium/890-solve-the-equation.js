// Source: https://leetcode.com/problems/solve-the-equation/   |   Difficulty: Medium
//
// Problem Description:
// Solve a given equation and return the value of 'x' in the form of a string "x=#value". The equation contains only '+', '-' operation, the variable 'x' and its coefficient. You should return "No solution" if there is no solution for the equation, or "Infinite solutions" if there are infinite solutions for the equation.
//
// If there is exactly one solution for the equation, we ensure that the value of 'x' is an integer.
//
// Example:
// Input: equation = "x+5-3+x=6+x-2"
// Output: "x=2"
//
// Constraints:
// 3 <= equation.length <= 1000
// 	equation has exactly one '='.
// 	equation consists of integers with an absolute value in the range [0, 100] without any leading zeros, and the variable 'x'.
// 	The input is generated that if there is a single solution, it will be an integer.
//
// Helpful references (internal KB):
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Finding the equation of a line for a segment (number, geometry, counting)
//   • When to use: Use this technique when representing and comparing lines in geometric algorithms, especially with real numbers, to improve numerical stability and reduce rounding errors.
//   • Idea: This method normalizes line equation coefficients (Ax + By + C = 0) by dividing them by sqrt(A^2 + B^2) to ensure A^2 + B^2 = 1. This improves numerical precision and enables unique line representation in O(1) time.
//   • Invariants: The normalized coefficients (A', B', C') define the same line as the original (A, B, C).; The sum of squares of the first two normalized coefficients, A'^2 + B'^2, is approximately 1.
//   • Tips: Always normalize line coefficients when working with real numbers.; Normalization helps in comparing lines robustly.
//   • Pitfalls: Not normalizing can lead to significant rounding errors.; Comparing unnormalized lines directly is unreliable.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} equation
 * @return {string}
 */
var solveEquation = function(equation) {
    const [left, right] = equation.split('=');
    const parse = (expr) => {
        let xCoeff = 0, constSum = 0, num = '', sign = 1;
        for (let i = 0; i < expr.length; i++) {
            const char = expr[i];
            if (char === 'x') {
                xCoeff += num === '' ? sign : sign * parseInt(num);
                num = '';
            } else if (char === '+' || char === '-') {
                if (num !== '') {
                    constSum += sign * parseInt(num);
                }
                sign = char === '+' ? 1 : -1;
                num = '';
            } else {
                num += char;
            }
        }
        if (num !== '') {
            constSum += sign * parseInt(num);
        }
        return [xCoeff, constSum];
    };
    const [xCoeffLeft, constSumLeft] = parse(left);
    const [xCoeffRight, constSumRight] = parse(right);
    const xCoeff = xCoeffLeft - xCoeffRight;
    const constSum = constSumRight - constSumLeft;
    if (xCoeff === 0) {
        return constSum === 0 ? "Infinite solutions" : "No solution";
    }
    return `x=${constSum / xCoeff}`;
};
