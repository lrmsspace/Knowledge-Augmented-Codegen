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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isRationalEqual(char* s, char* t) {
    /* Convert rational number in string form to a fraction (numerator, denominator) */
    void toFraction(const char *str, long long *num, long long *den) {
        const char *p = str;
        long long intPart = 0;
        while (*p && *p != '.' && *p != '(') {
            intPart = intPart * 10 + (*p - '0');
            p++;
        }
        long long numerator = intPart;
        long long denominator = 1;

        if (*p == '.') {
            p++;
            const char *nonRepStart = p;
            while (*p && *p != '(') p++;
            const char *nonRepEnd = p;

            for (const char *q = nonRepStart; q < nonRepEnd; q++) {
                numerator = numerator * 10 + (*q - '0');
                denominator *= 10;
            }

            if (*p == '(') {
                p++;
                const char *repStart = p;
                while (*p && *p != ')') p++;
                const char *repEnd = p;

                long long repNumerator = 0;
                long long repDenominator = 1;
                for (const char *q = repStart; q < repEnd; q++) {
                    repNumerator = repNumerator * 10 + (*q - '0');
                    repDenominator *= 10;
                }

                long long lenNonRep = nonRepEnd - nonRepStart;
                long long lenRep = repEnd - repStart;

                long long powNonRep = 1;
                for (long long i = 0; i < lenNonRep; i++) powNonRep *= 10;

                long long powRep = 1;
                for (long long i = 0; i < lenRep; i++) powRep *= 10;

                numerator = numerator * (powRep - 1) + repNumerator;
                denominator = denominator * (powRep - 1);
            }
        }

        /* Reduce fraction */
        long long a = numerator, b = denominator;
        while (b) {
            long long temp = b;
            b = a % b;
            a = temp;
        }
        *num = numerator / a;
        *den = denominator / a;
    }

    long long num1, den1, num2, den2;
    toFraction(s, &num1, &den1);
    toFraction(t, &num2, &den2);
    return num1 * den2 == num2 * den1;
}
