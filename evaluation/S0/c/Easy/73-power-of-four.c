// Source: https://leetcode.com/problems/power-of-four/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if it is a power of four. Otherwise, return false.
//
// An integer n is a power of four, if there exists an integer x such that n == 4x.
//
// Example:
// Input: n = 16
// Output: true
//
// Constraints:
// -231 <= n <= 231 - 1
//
//
//  
// Follow up: Could you solve it without loops/recursion?
//

bool isPowerOfFour(int n) {
    return n > 0 && (n & (n - 1)) == 0 && (n - 1) % 3 == 0;     
}
