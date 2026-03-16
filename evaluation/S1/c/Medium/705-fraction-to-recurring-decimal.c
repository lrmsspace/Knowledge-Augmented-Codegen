// Source: https://leetcode.com/problems/fraction-to-recurring-decimal/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
//
// If the fractional part is repeating, enclose the repeating part in parentheses
//
// If multiple answers are possible, return any of them.
//
// It is guaranteed that the length of the answer string is less than 104 for all the given inputs.
//
// Note that if the fraction can be represented as a finite length string, you must return it.
//
// Example:
// Input: numerator = 1, denominator = 2
// Output: "0.5"
//
// Constraints:
// -231 <= numerator, denominator <= 231 - 1
// 	denominator != 0
//
// Helpful references (internal KB):
// - Continued fractions (number, matrix-exp, segment-tree, recursion)
//   • When to use: When you need to represent real numbers as a sequence of integers, find optimal rational approximations, or solve certain number theoretic problems involving linear equations or quadratic irrationals.
//   • Idea: Continued fractions represent real numbers as an expression of the form a0 + 1/(a1 + 1/(a2 + ...)), providing a systematic way to find best rational approximations. They are fundamental in number theory, with convergent computation typically O(log N) for N terms.
//   • Invariants: The sequence of partial quotients (a_i) are positive integers for i >= 1.; Each convergent p_k/q_k is a best rational approximation of the original number.
//   • Tips: Understand the recursive definition and how to compute convergents.; The Euclidean algorithm is the basis for finite continued fractions.
//   • Pitfalls: Floating point precision issues when computing directly.; Incorrectly handling the base case or termination condition.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* fractionToDecimal(int numerator, int denominator) {
    // Handle zero numerator
    if (numerator == 0) {
        char *result = (char *)malloc(2 * sizeof(char));
        strcpy(result, "0");
        return result;
    }

    // Initialize result string
    char *result = (char *)malloc(50 * sizeof(char));
    int index = 0;

    // Determine the sign
    if ((numerator < 0) ^ (denominator < 0)) {
        result[index++] = '-';
    }

    // Work with absolute values
    long long num = llabs((long long)numerator);
    long long den = llabs((long long)denominator);

    // Append the integer part
    long long integerPart = num / den;
    index += sprintf(result + index, "%lld", integerPart);

    // Calculate the remainder
    long long remainder = num % den;
    if (remainder == 0) {
        result[index] = '\0';
        return result;
    }

    // Append the decimal point
    result[index++] = '.';

    // Map to store remainders and their corresponding indices in the result
    int *remainderMap = (int *)calloc(den, sizeof(int));
    for (int i = 0; i < den; i++) {
        remainderMap[i] = -1;
    }

    // Process the fractional part
    while (remainder != 0) {
        // Check if this remainder has been seen before
        if (remainderMap[remainder] != -1) {
            int insertIndex = remainderMap[remainder];
            // Insert parentheses
            for (int j = index; j >= insertIndex; j--) {
                result[j + 1] = result[j];
            }
            result[insertIndex] = '(';
            index++;
            result[index++] = ')';
            break;
        }

        // Store the index of this remainder
        remainderMap[remainder] = index;

        // Update remainder
        remainder *= 10;
        long long fractionalDigit = remainder / den;
        result[index++] = '0' + fractionalDigit;
        remainder %= den;
    }

    result[index] = '\0';
    free(remainderMap);
    return result;      
}
