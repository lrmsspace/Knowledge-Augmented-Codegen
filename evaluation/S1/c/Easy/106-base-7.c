// Source: https://leetcode.com/problems/base-7/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer num, return a string of its base 7 representation.
//
// Example:
// Input: num = 100
// Output: "202"
//
// Constraints:
// -107 <= num <= 107
//
// Helpful references (internal KB):
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - String Hashing (string, number, hashing)
//   • When to use: When comparing strings or substrings efficiently, especially for equality checks or finding duplicates, to reduce comparison time from O(m) to O(1) on average.
//   • Idea: String hashing converts a string into a numerical value (hash) using a polynomial rolling hash function, allowing for O(1) average-case comparison of strings or substrings. This technique typically involves modular arithmetic to keep hash values within a manageable range.
//   • Invariants: The hash of any prefix s[0...i] is correctly calculated based on the chosen base and modulus.; Precomputed powers of the base 'p' are available and correct for all required string lengths.
//   • Tips: Convert characters to integers starting from 1 (e.g., 'a' -> 1) to avoid zero hashes for strings like 'a', 'aa'.; Precompute powers of the base 'p' and their modular inverses for efficient rolling hash calculations.
//   • Pitfalls: Choosing 'a' -> 0 can lead to identical hashes for strings like 'a', 'aa', 'aaa', causing false positives.; Using a single hash function can lead to collisions, where different strings produce the same hash, requiring careful handling.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* convertToBase7(int num) {
    if (num == 0) {
        char* result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int isNegative = num < 0 ? 1 : 0;
    if (isNegative) {
        num = -num;
    }

    char buffer[32];
    int index = 0;

    while (num > 0) {
        int remainder = num % 7;
        buffer[index++] = '0' + remainder;
        num /= 7;
    }

    if (isNegative) {
        buffer[index++] = '-';
    }

    char* result = (char*)malloc((index + 1) * sizeof(char));
    for (int i = 0; i < index; i++) {
        result[i] = buffer[index - i - 1];
    }
    result[index] = '\0';

    return result;      
}
