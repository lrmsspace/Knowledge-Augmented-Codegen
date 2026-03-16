// Source: https://leetcode.com/problems/reverse-integer/   |   Difficulty: Medium
//
// Problem Description:
// Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.
//
// Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
//
// Example:
// Input: x = 123
// Output: 321
//
// Constraints:
// -231 <= x <= 231 - 1
//

int reverse(int x){
    int reversed = 0;
    while (x != 0) {
        int digit = x % 10;
        x /= 10;

        // Check for overflow/underflow before multiplying and adding
        if (reversed > (INT_MAX - digit) / 10) return 0; // Overflow
        if (reversed < (INT_MIN - digit) / 10) return 0; // Underflow

        reversed = reversed * 10 + digit;
    }
    return reversed;
}
