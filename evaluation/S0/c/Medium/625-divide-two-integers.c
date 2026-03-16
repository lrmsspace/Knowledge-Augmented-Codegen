// Source: https://leetcode.com/problems/divide-two-integers/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
//
// The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.
//
// Return the quotient after dividing dividend by divisor.
//
// Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For this problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1, and if the quotient is strictly less than -231, then return -231.
//
// Example:
// Input: dividend = 10, divisor = 3
// Output: 3
// Explanation: 10/3 = 3.33333.. which is truncated to 3.
//
// Constraints:
// -231 <= dividend, divisor <= 231 - 1
// 	divisor != 0
//

int divide(int dividend, int divisor) {
    // Handle edge case for overflow
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }

    // Determine the sign of the quotient
    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;

    // Work with absolute values to simplify the division logic
    long long abs_dividend = llabs((long long)dividend);
    long long abs_divisor = llabs((long long)divisor);

    long long quotient = 0;
    while (abs_dividend >= abs_divisor) {
        long long temp = abs_divisor, multiple = 1;
        while (abs_dividend >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }
        abs_dividend -= temp;
        quotient += multiple;
    }

    // Apply the sign to the quotient
    quotient = sign * quotient;

    return (int)quotient;       
}
