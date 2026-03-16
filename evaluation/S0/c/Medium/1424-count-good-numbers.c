// Source: https://leetcode.com/problems/count-good-numbers/   |   Difficulty: Medium
//
// Problem Description:
// A digit string is good if the digits (0-indexed) at even indices are even and the digits at odd indices are prime (2, 3, 5, or 7).
//
//
// 	For example, "2582" is good because the digits (2 and 8) at even positions are even and the digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an even index but is not even.
//
//
// Given an integer n, return the total number of good digit strings of length n. Since the answer may be large, return it modulo 109 + 7.
//
// A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".
//
// Constraints:
// 1 <= n <= 1015
//

int countGoodNumbers(long long n) {
    const int MOD = 1e9 + 7;
    long long even_positions = (n + 1) / 2;
    long long odd_positions = n / 2;

    long long even_choices = 1;
    long long odd_choices = 1;

    // Calculate 5^even_positions % MOD
    for (long long i = 0; i < even_positions; i++) {
        even_choices = (even_choices * 5) % MOD;
    }

    // Calculate 4^odd_positions % MOD
    for (long long i = 0; i < odd_positions; i++) {
        odd_choices = (odd_choices * 4) % MOD;
    }

    return (even_choices * odd_choices) % MOD;      
}
