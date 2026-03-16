// Source: https://leetcode.com/problems/integer-to-english-words/   |   Difficulty: Hard
//
// Problem Description:
// Convert a non-negative integer num to its English words representation.
//
// Example:
// Input: num = 123
// Output: "One Hundred Twenty Three"
//
// Constraints:
// 0 <= num <= 231 - 1
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
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* numberToWords(int num) {
    if (num == 0) return "Zero";

    const char *below_20[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                              "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                              "Seventeen", "Eighteen", "Nineteen"};
    const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const char *thousands[] = {"", "Thousand", "Million", "Billion"};

    char *result = (char *)malloc(512); // Allocate enough space
    result[0] = '\0';
    int idx = 0;

    for (int i = 0; i < 4 && num > 0; i++) {
        int chunk = num % 1000;
        if (chunk != 0) {
            char chunkStr[128] = "";
            if (chunk >= 100) {
                idx += sprintf(chunkStr + idx, "%s Hundred ", below_20[chunk / 100]);
                chunk %= 100;
            }
            if (chunk >= 20) {
                idx += sprintf(chunkStr + idx, "%s ", tens[chunk / 10]);
                chunk %= 10;
            }
            if (chunk > 0) {
                idx += sprintf(chunkStr + idx, "%s ", below_20[chunk]);
            }
            if (thousands[i][0] != '\0') {
                idx += sprintf(chunkStr + idx, "%s ", thousands[i]);
            }
            // Prepend chunkStr to result
            char temp[512];
            strcpy(temp, chunkStr);
            strcat(temp, result);
            strcpy(result, temp);
        }
        num /= 1000;
        idx = 0; // Reset index for next chunk
    }

    // Remove trailing space
    int len = strlen(result);
    if (len > 0 && result[len - 1] == ' ') {
        result[len - 1] = '\0';
    }

    return result;      
}
