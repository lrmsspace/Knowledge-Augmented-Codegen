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

class Solution {
    public int reverse(int x) {
        int reversed = 0;
        while (x != 0) {
            int digit = x % 10;
            x /= 10;

            // Check for overflow before actually updating reversed
            if (reversed > Integer.MAX_VALUE / 10 || (reversed == Integer.MAX_VALUE / 10 && digit > 7)) {
                return 0; // Overflow will occur
            }
            if (reversed < Integer.MIN_VALUE / 10 || (reversed == Integer.MIN_VALUE / 10 && digit < -8)) {
                return 0; // Underflow will occur
            }

            reversed = reversed * 10 + digit;
        }
        return reversed;            
    }
}
