// Source: https://leetcode.com/problems/maximum-value-after-insertion/   |   Difficulty: Medium
//
// Problem Description:
// You are given a very large integer n, represented as a string,​​​​​​ and an integer digit x. The digits in n and the digit x are in the inclusive range [1, 9], and n may represent a negative number.
//
// You want to maximize n's numerical value by inserting x anywhere in the decimal representation of n​​​​​​. You cannot insert x to the left of the negative sign.
//
//
// 	For example, if n = 73 and x = 6, it would be best to insert it between 7 and 3, making n = 763.
// 	If n = -55 and x = 2, it would be best to insert it before the first 5, making n = -255.
//
//
// Return a string representing the maximum value of n​​​​​​ after the insertion.
//
// Example:
// Input: n = "99", x = 9
// Output: "999"
// Explanation: The result is the same regardless of where you insert 9.
//
// Constraints:
// 1 <= n.length <= 105
// 	1 <= x <= 9
// 	The digits in n​​​ are in the range [1, 9].
// 	n is a valid representation of an integer.
// 	In the case of a negative n,​​​​​​ it will begin with '-'.
//
// Helpful references (internal KB):
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* maxValue(char* n, int x) {
    int len = 0;
    while (n[len] != '\0') {
        len++;
    }

    char* result = (char*)malloc((len + 2) * sizeof(char)); // +1 for x and +1 for null terminator
    if (!result) {
        return NULL; // Handle memory allocation failure
    }

    int i = 0, j = 0;
    if (n[0] == '-') {
        result[j++] = '-';
        i++;
        while (n[i] != '\0' && n[i] <= x + '0') {
            result[j++] = n[i++];
        }
    } else {
        while (n[i] != '\0' && n[i] >= x + '0') {
            result[j++] = n[i++];
        }
    }

    result[j++] = x + '0'; // Insert x
    while (n[i] != '\0') {
        result[j++] = n[i++];
    }
    result[j] = '\0'; // Null-terminate the string

    return result;      
}
