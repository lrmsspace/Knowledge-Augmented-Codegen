// Source: https://leetcode.com/problems/binary-number-with-alternating-bits/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.
//
// Example:
// Input: n = 5
// Output: true
// Explanation: The binary representation of 5 is: 101
//
// Constraints:
// 1 <= n <= 231 - 1
//

bool hasAlternatingBits(int n) {
    int prev_bit = -1;
    while (n > 0) {
        int current_bit = n & 1;
        if (current_bit == prev_bit) {
            return false;
        }
        prev_bit = current_bit;
        n >>= 1;
    }
    return true;        
}
