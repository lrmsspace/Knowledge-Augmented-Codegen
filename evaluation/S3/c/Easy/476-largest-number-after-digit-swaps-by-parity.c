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
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - String Sorts (array, string, number, radix-sort, recursion, counting-sort)
//   • When to use: Use when sorting a large collection of strings or integers with a limited range of character/digit values. It is particularly efficient for fixed-length keys but can be adapted for variable lengths.
//   • Idea: Radix sort is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by individual digits or characters which share the same significant position and value. It typically achieves O(N*W) time complexity, where N is the number of items and W is the key length.
//   • Invariants: After each pass `d`, the elements are stably sorted according to their digits up to position `d`.; The counting sort subroutine correctly places elements into their sorted positions for the current digit, preserving relative order.
//   • Tips: LSD (Least Significant Digit) is simpler for fixed-length keys.; MSD (Most Significant Digit) is better for variable-length keys or when keys are very long.
//   • Pitfalls: Not efficient for small N or very large W due to constant factors.; Requires extra space for auxiliary array and counting array.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int largestInteger(int num) {
    char str[12]; // Enough to hold digits of num and null terminator
    sprintf(str, "%d", num); // Convert number to string

    int odd_digits[10], even_digits[10];
    int odd_count = 0, even_count = 0;

    // Separate odd and even digits
    for (int i = 0; str[i] != '\0'; i++) {
        int digit = str[i] - '0';
        if (digit % 2 == 0) {
            even_digits[even_count++] = digit;
        } else {
            odd_digits[odd_count++] = digit;
        }
    }

    // Sort odd and even digits in descending order
    for (int i = 0; i < odd_count - 1; i++) {
        for (int j = 0; j < odd_count - i - 1; j++) {
            if (odd_digits[j] < odd_digits[j + 1]) {
                int temp = odd_digits[j];
                odd_digits[j] = odd_digits[j + 1];
                odd_digits[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < even_count - 1; i++) {
        for (int j = 0; j < even_count - i - 1; j++) {
            if (even_digits[j] < even_digits[j + 1]) {
                int temp = even_digits[j];
                even_digits[j] = even_digits[j + 1];
                even_digits[j + 1] = temp;
            }
        }
    }

    // Reconstruct the largest number by replacing digits in original positions
    int odd_index = 0, even_index = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        int digit = str[i] - '0';
        if (digit % 2 == 0) {
            str[i] = even_digits[even_index++] + '0';
        } else {
            str[i] = odd_digits[odd_index++] + '0';
        }
    }

    return atoi(str); // Convert back to integer        
}
