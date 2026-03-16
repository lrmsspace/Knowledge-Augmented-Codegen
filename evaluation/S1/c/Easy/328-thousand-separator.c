// Source: https://leetcode.com/problems/thousand-separator/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, add a dot (".") as the thousands separator and return it in string format.
//
// Example:
// Input: n = 987
// Output: "987"
//
// Constraints:
// 0 <= n <= 231 - 1
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* thousandSeparator(int n) {
    // Convert integer n to string
    char buffer[15]; // Enough to hold max int with separators
    int len = 0;
    if (n == 0) {
        buffer[len++] = '0';
    } else {
        while (n > 0) {
            buffer[len++] = (n % 10) + '0';
            n /= 10;
        }
    }

    // Insert dots as thousand separators
    char result[20]; // Enough to hold the final string with separators
    int resultLen = 0;
    for (int i = 0; i < len; i++) {
        if (i > 0 && i % 3 == 0) {
            result[resultLen++] = '.';
        }
        result[resultLen++] = buffer[i];
    }

    // Reverse the result string
    for (int i = 0; i < resultLen / 2; i++) {
        char temp = result[i];
        result[i] = result[resultLen - 1 - i];
        result[resultLen - 1 - i] = temp;
    }
    result[resultLen] = '\0';

    // Allocate memory for the return string
    char* finalResult = (char*)malloc((resultLen + 1) * sizeof(char));
    for (int i = 0; i <= resultLen; i++) {
        finalResult[i] = result[i];
    }

    return finalResult;     
}
