// Source: https://leetcode.com/problems/factorial-trailing-zeroes/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of trailing zeroes in n!.
//
// Note that n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1.
//
// Example:
// Input: n = 3
// Output: 0
// Explanation: 3! = 6, no trailing zero.
//
// Constraints:
// 0 <= n <= 104
//
//
//  
// Follow up: Could you write a solution that works in logarithmic time complexity?
//

int trailingZeroes(int n) {
    int count = 0;
    while (n >= 5) {
        n /= 5;
        count += n;
    }
    return count;       
}
