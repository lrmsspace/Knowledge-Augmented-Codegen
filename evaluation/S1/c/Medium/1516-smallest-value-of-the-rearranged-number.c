// Source: https://leetcode.com/problems/smallest-value-of-the-rearranged-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. Rearrange the digits of num such that its value is minimized and it does not contain any leading zeros.
//
// Return the rearranged number with minimal value.
//
// Note that the sign of the number does not change after rearranging the digits.
//
// Example:
// Input: num = 310
// Output: 103
// Explanation: The possible arrangements for the digits of 310 are 013, 031, 103, 130, 301, 310. 
// The arrangement with the smallest value that does not contain any leading zeros is 103.
//
// Constraints:
// -1015 <= num <= 1015
//
// Helpful references (internal KB):
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long smallestNumber(long long num) {
    if (num == 0) {
        return 0;
    }

    int is_negative = num < 0 ? 1 : 0;
    if (is_negative) {
        num = -num;
    }

    int digit_count[10] = {0};
    while (num > 0) {
        int digit = num % 10;
        digit_count[digit]++;
        num /= 10;
    }

    long long result = 0;
    if (is_negative) {
        for (int digit = 9; digit >= 0; digit--) {
            while (digit_count[digit] > 0) {
                result = result * 10 + digit;
                digit_count[digit]--;
            }
        }
        result = -result;
    } else {
        for (int digit = 1; digit <= 9; digit++) {
            if (digit_count[digit] > 0) {
                result = digit;
                digit_count[digit]--;
                break;
            }
        }
        for (int digit = 0; digit <= 9; digit++) {
            while (digit_count[digit] > 0) {
                result = result * 10 + digit;
                digit_count[digit]--;
            }
        }
    }

    return result;      
}
