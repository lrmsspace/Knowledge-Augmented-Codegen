// Source: https://leetcode.com/problems/ugly-number-ii/   |   Difficulty: Medium
//
// Problem Description:
// An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
//
// Given an integer n, return the nth ugly number.
//
// Example:
// Input: n = 10
// Output: 12
// Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.
//
// Constraints:
// 1 <= n <= 1690
//

int nthUglyNumber(int n) {
    int ugly_numbers[n];
    ugly_numbers[0] = 1;

    int i2 = 0, i3 = 0, i5 = 0;
    int next_multiple_of_2 = 2;
    int next_multiple_of_3 = 3;
    int next_multiple_of_5 = 5;

    for (int i = 1; i < n; i++) {
        int next_ugly_number = next_multiple_of_2;
        if (next_multiple_of_3 < next_ugly_number) {
            next_ugly_number = next_multiple_of_3;
        }
        if (next_multiple_of_5 < next_ugly_number) {
            next_ugly_number = next_multiple_of_5;
        }

        ugly_numbers[i] = next_ugly_number;

        if (next_ugly_number == next_multiple_of_2) {
            i2++;
            next_multiple_of_2 = ugly_numbers[i2] * 2;
        }
        if (next_ugly_number == next_multiple_of_3) {
            i3++;
            next_multiple_of_3 = ugly_numbers[i3] * 3;
        }
        if (next_ugly_number == next_multiple_of_5) {
            i5++;
            next_multiple_of_5 = ugly_numbers[i5] * 5;
        }
    }

    return ugly_numbers[n - 1];     
}
