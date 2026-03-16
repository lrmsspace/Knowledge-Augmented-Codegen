// Source: https://leetcode.com/problems/strictly-palindromic-number/   |   Difficulty: Medium
//
// Problem Description:
// An integer n is strictly palindromic if, for every base b between 2 and n - 2 (inclusive), the string representation of the integer n in base b is palindromic.
//
// Given an integer n, return true if n is strictly palindromic and false otherwise.
//
// A string is palindromic if it reads the same forward and backward.
//
// Example:
// Input: n = 9
// Output: false
// Explanation: In base 2: 9 = 1001 (base 2), which is palindromic.
// In base 3: 9 = 100 (base 3), which is not palindromic.
// Therefore, 9 is not strictly palindromic so we return false.
// Note that in bases 4, 5, 6, and 7, n = 9 is also not palindromic.
//
// Constraints:
// 4 <= n <= 105
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Binary Exponentiation (number, mod-exp, recursion)
//   • When to use: Use this algorithm to efficiently compute large integer powers of a number, especially when results need to be taken modulo a specific value. It is crucial for problems requiring powers with large exponents.
//   • Idea: Binary exponentiation, also known as exponentiation by squaring, computes a^n by breaking down the exponent n into its binary representation. This method significantly reduces the number of multiplications required, achieving an O(log n) time complexity.
//   • Invariants: In the iterative approach, (current_result * (original_base ^ original_exponent)) remains constant.; The exponent n is always non-negative and decreases towards zero.
//   • Tips: Apply the modulo operation at each multiplication step to prevent intermediate overflow.; The iterative approach is generally preferred over recursion to avoid potential stack overflow for very large exponents.
//   • Pitfalls: Forgetting to apply modulo at each step can lead to integer overflow, especially with large bases.; Incorrectly handling the base case for n=0 or n=1.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <stdlib.h>
#include <stdbool.h>

/* Convert n to base b and check if its representation is palindromic */
static bool isPalindromeInBase(int n, int base) {
    /* Get digits of n in base b */
    int digits[32]; /* sufficient for n <= 10^5 in base 2 */
    int len = 0;
    int temp = n;
    while (temp > 0) {
        digits[len++] = temp % base;
        temp /= base;
    }
    
    /* Check if palindromic */
    for (int i = 0; i < len / 2; ++i) {
        if (digits[i] != digits[len - 1 - i]) return false;
    }
    return true;
}

bool isStrictlyPalindromic(int n) {
    /* Check for all bases from 2 to n-2 */
    for (int base = 2; base <= n - 2; ++base) {
        if (!isPalindromeInBase(n, base)) return false;
    }
    return true;
}
