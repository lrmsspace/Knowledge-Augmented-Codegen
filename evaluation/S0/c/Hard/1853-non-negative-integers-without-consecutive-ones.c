// Source: https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/   |   Difficulty: Hard
//
// Problem Description:
// Given a positive integer n, return the number of the integers in the range [0, n] whose binary representations do not contain consecutive ones.
//
// Example:
// Input: n = 5
// Output: 5
// Explanation:
// Here are the non-negative integers <= 5 with their corresponding binary representations:
// 0 : 0
// 1 : 1
// 2 : 10
// 3 : 11
// 4 : 100
// 5 : 101
// Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule.
//
// Constraints:
// 1 <= n <= 109
//

int findIntegers(int n) {
    int fib[32];
    fib[0] = 1; fib[1] = 2;
    for (int i = 2; i < 32; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    int prev_bit = 0;
    int result = 0;
    for (int k = 30; k >= 0; k--) {
        if (n & (1 << k)) {
            result += fib[k];
            if (prev_bit) {
                return result;
            }
            prev_bit = 1;
        } else {
            prev_bit = 0;
        }
    }
    return result + 1;      
}
