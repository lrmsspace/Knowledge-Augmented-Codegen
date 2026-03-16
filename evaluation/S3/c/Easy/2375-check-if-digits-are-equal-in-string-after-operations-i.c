// Source: https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting of digits. Perform the following operation repeatedly until the string has exactly two digits:
//
//
// 	For each pair of consecutive digits in s, starting from the first digit, calculate a new digit as the sum of the two digits modulo 10.
// 	Replace s with the sequence of newly calculated digits, maintaining the order in which they are computed.
//
//
// Return true if the final two digits in s are the same; otherwise, return false.
//
// Example:
// Input: s = "3902"
//
// Output: true
//
// Explanation:
//
//
// 	Initially, s = "3902"
// 	First operation:
// 	
// 		(s[0] + s[1]) % 10 = (3 + 9) % 10 = 2
// 		(s[1] + s[2]) % 10 = (9 + 0) % 10 = 9
// 		(s[2] + s[3]) % 10 = (0 + 2) % 10 = 2
// 		s becomes "292"
// 	
// 	
// 	Second operation:
// 	
// 		(s[0] + s[1]) % 10 = (2 + 9) % 10 = 1
// 		(s[1] + s[2]) % 10 = (9 + 2) % 10 = 1
// 		s becomes "11"
// 	
// 	
// 	Since the digits in "11" are the same, the output is true.
//
// Constraints:
// 3 <= s.length <= 100
// 	s consists of only digits.
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
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool hasSameDigits(char* s) {
    int n = strlen(s);
    while (n > 2) {
        for (int i = 0; i < n - 1; i++) {
            s[i] = ((s[i] - '0') + (s[i + 1] - '0')) % 10 + '0';
        }
        n--;
    }
    return s[0] == s[1];        
}
