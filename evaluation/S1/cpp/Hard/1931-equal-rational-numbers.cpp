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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isRationalEqual(string s, string t) {
        // Helper function to parse the rational number string
        auto parseRational = [](const string& str, long long& numerator, long long& denominator) {
            size_t pos = str.find('(');
            string nonRepeating = (pos == string::npos) ? str : str.substr(0, pos);
            string repeating = (pos == string::npos) ? "" : str.substr(pos + 1, str.length() - pos - 2);

            size_t dotPos = nonRepeating.find('.');
            string integerPart = (dotPos == string::npos) ? nonRepeating : nonRepeating.substr(0, dotPos);
            string fractionalPart = (dotPos == string::npos) ? "" : nonRepeating.substr(dotPos + 1);

            long long intPart = stoll(integerPart.empty() ? "0" : integerPart);
            long long fracPart = 0;
            long long repeatPart = 0;

            if (!fractionalPart.empty()) {
                fracPart = stoll(fractionalPart);
            }

            if (!repeating.empty()) {
                repeatPart = stoll(repeating);
            }

            long long fracLen = fractionalPart.length();
            long long repeatLen = repeating.length();

            if (repeatLen > 0) {
                denominator = pow(10, fracLen) * (pow(10, repeatLen) - 1);
                numerator = intPart * denominator + fracPart * (pow(10, repeatLen) - 1) + repeatPart;
            } else {
                denominator = pow(10, fracLen);
                numerator = intPart * denominator + fracPart;
            }
        };

        long long num1, den1, num2, den2;
        parseRational(s, num1, den1);
        parseRational(t, num2, den2);

        return num1 * den2 == num2 * den1;          
    }
};
