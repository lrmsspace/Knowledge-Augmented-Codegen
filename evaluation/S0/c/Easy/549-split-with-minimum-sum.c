// Source: https://leetcode.com/problems/split-with-minimum-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num, split it into two non-negative integers num1 and num2 such that:
//
//
// 	The concatenation of num1 and num2 is a permutation of num.
//
// 	
// 		In other words, the sum of the number of occurrences of each digit in num1 and num2 is equal to the number of occurrences of that digit in num.
// 	
// 	
// 	num1 and num2 can contain leading zeros.
//
//
// Return the minimum possible sum of num1 and num2.
//
// Example:
// Input: num = 4325
// Output: 59
// Explanation: We can split 4325 so that num1 is 24 and num2 is 35, giving a sum of 59. We can prove that 59 is indeed the minimal possible sum.
//
// Constraints:
// 10 <= num <= 109
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int splitNum(int num) {
    int digits[10] = {0};
    while (num > 0) {
        digits[num % 10]++;
        num /= 10;
    }

    int num1 = 0, num2 = 0;
    int turn = 0; // 0 for num1, 1 for num2

    for (int digit = 0; digit <= 9; digit++) {
        while (digits[digit] > 0) {
            if (turn == 0) {
                num1 = num1 * 10 + digit;
                turn = 1;
            } else {
                num2 = num2 * 10 + digit;
                turn = 0;
            }
            digits[digit]--;
        }
    }

    return num1 + num2;     
}
