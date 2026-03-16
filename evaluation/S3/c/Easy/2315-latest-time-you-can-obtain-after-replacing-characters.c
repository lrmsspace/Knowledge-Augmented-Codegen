// Source: https://leetcode.com/problems/latest-time-you-can-obtain-after-replacing-characters/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s representing a 12-hour format time where some of the digits (possibly none) are replaced with a "?".
//
// 12-hour times are formatted as "HH:MM", where HH is between 00 and 11, and MM is between 00 and 59. The earliest 12-hour time is 00:00, and the latest is 11:59.
//
// You have to replace all the "?" characters in s with digits such that the time we obtain by the resulting string is a valid 12-hour format time and is the latest possible.
//
// Return the resulting string.
//
// Example:
// Input: s = "1?:?4"
//
// Output: "11:54"
//
// Explanation: The latest 12-hour format time we can achieve by replacing "?" characters is "11:54".
//
// Constraints:
// s.length == 5
// 	s[2] is equal to the character ":".
// 	All characters except s[2] are digits or "?" characters.
// 	The input is generated such that there is at least one time between "00:00" and "11:59" that you can obtain after replacing the "?" characters.
//
// Helpful references (internal KB):
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* findLatestTime(char* s) {
    char* result = (char*)malloc(6 * sizeof(char)); // "HH:MM" + null terminator
    result[5] = '\0'; // Null-terminate the string

    // Process hours
    if (s[0] == '?') {
        if (s[1] == '?' || s[1] <= '3') {
            result[0] = '1'; // Can be 10 or 11
        } else {
            result[0] = '0'; // Must be 00-09
        }
    } else {
        result[0] = s[0]; // Keep the known digit
    }

    if (s[1] == '?') {
        if (result[0] == '1') {
            result[1] = '1'; // Can be 10 or 11
        } else {
            result[1] = '9'; // Can be 00-09
        }
    } else {
        result[1] = s[1]; // Keep the known digit
    }

    // Process minutes
    if (s[3] == '?') {
        result[3] = '5'; // Can be 00-59
    } else {
        result[3] = s[3]; // Keep the known digit
    }

    if (s[4] == '?') {
        result[4] = '9'; // Can be 00-59
    } else {
        result[4] = s[4]; // Keep the known digit
    }

    return result;      
}
