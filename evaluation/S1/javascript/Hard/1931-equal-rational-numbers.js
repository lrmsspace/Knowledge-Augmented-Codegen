// Source: https://leetcode.com/problems/equal-rational-numbers/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, each of which represents a non-negative rational number, return true if and only if they represent the same number. The strings may use parentheses to denote the repeating part of the rational number.
//
// A rational number can be represented using up to three parts: <IntegerPart>, <NonRepeatingPart>, and a <RepeatingPart>. The number will be represented in one of the following three ways:
//
//
// 	<IntegerPart>
//
// 	
// 		For example, 12, 0, and 123.
// 	
// 	
// 	<IntegerPart><.><NonRepeatingPart>
// 	
// 		For example, 0.5, 1., 2.12, and 123.0001.
// 	
// 	
// 	<IntegerPart><.><NonRepeatingPart><(><RepeatingPart><)>
// 	
// 		For example, 0.1(6), 1.(9), 123.00(1212).
// 	
// 	
//
//
// The repeating portion of a decimal expansion is conventionally denoted within a pair of round brackets. For example:
//
//
// 	1/6 = 0.16666666... = 0.1(6) = 0.1666(6) = 0.166(66).
//
// Example:
// Input: s = "0.(52)", t = "0.5(25)"
// Output: true
// Explanation: Because "0.(52)" represents 0.52525252..., and "0.5(25)" represents 0.52525252525..... , the strings represent the same number.
//
// Constraints:
// Each part consists only of digits.
// 	The <IntegerPart> does not have leading zeros (except for the zero itself).
// 	1 <= <IntegerPart>.length <= 4
// 	0 <= <NonRepeatingPart>.length <= 4
// 	1 <= <RepeatingPart>.length <= 4
//
// Helpful references (internal KB):
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two or more integers, or as a subroutine for tasks like simplifying fractions or finding the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the division algorithm. It operates in logarithmic time complexity, O(log min(a, b)).
//   • Invariants: The greatest common divisor of the current pair (a, b) remains constant and equal to the GCD of the original inputs.; The second number (b) is always non-negative.
//   • Tips: Handle the base case where one of the numbers is zero; gcd(a, 0) = a.; The algorithm works for any order of inputs; if a < b, the first step swaps them effectively.
//   • Pitfalls: Forgetting to take absolute values if negative inputs are possible, as GCD is typically defined for non-negative integers.; Incorrectly handling the zero input case, which can lead to infinite loops or incorrect results.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Continued fractions (number, matrix-exp, segment-tree, recursion)
//   • When to use: When you need to represent real numbers as a sequence of integers, find optimal rational approximations, or solve certain number theoretic problems involving linear equations or quadratic irrationals.
//   • Idea: Continued fractions represent real numbers as an expression of the form a0 + 1/(a1 + 1/(a2 + ...)), providing a systematic way to find best rational approximations. They are fundamental in number theory, with convergent computation typically O(log N) for N terms.
//   • Invariants: The sequence of partial quotients (a_i) are positive integers for i >= 1.; Each convergent p_k/q_k is a best rational approximation of the original number.
//   • Tips: Understand the recursive definition and how to compute convergents.; The Euclidean algorithm is the basis for finite continued fractions.
//   • Pitfalls: Floating point precision issues when computing directly.; Incorrectly handling the base case or termination condition.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isRationalEqual = function(s, t) {
    const parseRational = (str) => {
        const [integerPart, decimalPart = ''] = str.split('.');
        const [nonRepeatingPart = '', repeatingPart = ''] = decimalPart.split('(').concat(['']);
        return { integerPart, nonRepeatingPart, repeatingPart };
    };

    const toFraction = ({ integerPart, nonRepeatingPart, repeatingPart }) => {
        let numerator = BigInt(integerPart);
        if (nonRepeatingPart) {
            numerator = numerator * BigInt(10 ** nonRepeatingPart.length) + BigInt(nonRepeatingPart);
        }
        if (repeatingPart) {
            const repeatLength = repeatingPart.length;
            const nonRepeatLength = nonRepeatingPart.length;
            const repeatValue = BigInt(repeatingPart);
            numerator = numerator * BigInt(10 ** repeatLength) + repeatValue - (nonRepeatLength > 0 ? BigInt(nonRepeatingPart) : 0);
            const denominator = BigInt(10 ** (nonRepeatLength + repeatLength)) - BigInt(10 ** nonRepeatLength);
            return [numerator, denominator];
        } else {
            return [numerator, BigInt(10 ** nonRepeatingPart.length)];
        }
    };

    const gcd = (a, b) => {
        while (b) {
            [a, b] = [b, a % b];
        }
        return a;
    };

    const fracS = toFraction(parseRational(s));
    const fracT = toFraction(parseRational(t));

    const g1 = gcd(fracS[0], fracS[1]);
    const g2 = gcd(fracT[0], fracT[1]);

    return fracS[0] / g1 === fracT[0] / g2 && fracS[1] / g1 === fracT[1] / g2;
};
