// Source: https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer num. You may swap any two digits of num that have the same parity (i.e. both odd digits or both even digits).
//
// Return the largest possible value of num after any number of swaps.
//
// Example:
// Input: num = 1234
// Output: 3412
// Explanation: Swap the digit 3 with the digit 1, this results in the number 3214.
// Swap the digit 2 with the digit 4, this results in the number 3412.
// Note that there may be other sequences of swaps but it can be shown that 3412 is the largest possible number.
// Also note that we may not swap the digit 4 with the digit 1 since they are of different parities.
//
// Constraints:
// 1 <= num <= 109
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
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

int largestInteger(int num) {
    int even_digits[10];
    int odd_digits[10];
    int even_count = 0;
    int odd_count = 0;
    int temp = num;

    // Separate digits into even and odd arrays
    while (temp > 0) {
        int digit = temp % 10;
        if (digit % 2 == 0) {
            even_digits[even_count++] = digit;
        } else {
            odd_digits[odd_count++] = digit;
        }
        temp /= 10;
    }

    // Sort even and odd digits in descending order
    for (int i = 0; i < even_count - 1; i++) {
        for (int j = i + 1; j < even_count; j++) {
            if (even_digits[i] < even_digits[j]) {
                int swap = even_digits[i];
                even_digits[i] = even_digits[j];
                even_digits[j] = swap;
            }
        }
    }

    for (int i = 0; i < odd_count - 1; i++) {
        for (int j = i + 1; j < odd_count; j++) {
            if (odd_digits[i] < odd_digits[j]) {
                int swap = odd_digits[i];
                odd_digits[i] = odd_digits[j];
                odd_digits[j] = swap;
            }
        }
    }

    // Reconstruct the largest number by swapping digits based on parity
    int result = 0;
    int even_index = 0;
    int odd_index = 0;
    temp = num;

    while (temp > 0) {
        int digit = temp % 10;
        if (digit % 2 == 0) {
            result += even_digits[even_index++] * pow(10, (int)log10(num) - (int)log10(temp));
        } else {
            result += odd_digits[odd_index++] * pow(10, (int)log10(num) - (int)log10(temp));
        }
        temp /= 10;
    }

    return result;      
}
