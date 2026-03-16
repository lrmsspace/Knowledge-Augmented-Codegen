// Source: https://leetcode.com/problems/calculate-money-in-leetcode-bank/   |   Difficulty: Easy
//
// Problem Description:
// Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.
//
// He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday, he will put in $1 more than the day before. On every subsequent Monday, he will put in $1 more than the previous Monday. 
//
// Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth day.
//
// Example:
// Input: n = 4
// Output: 10
// Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.
//
// Constraints:
// 1 <= n <= 1000
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int totalMoney(int n) {
    int total = 0;
    int week = n / 7; // Number of complete weeks
    int day = n % 7;  // Remaining days after complete weeks

    // Calculate total for complete weeks
    total += week * (28 + (week - 1) * 7) / 2; // Sum of arithmetic series for complete weeks

    // Calculate total for remaining days
    for (int i = 0; i < day; i++) {
        total += week + i + 1; // Money saved on the remaining days
    }

    return total;       
}
