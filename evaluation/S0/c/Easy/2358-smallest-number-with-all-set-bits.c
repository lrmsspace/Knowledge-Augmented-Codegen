// Source: https://leetcode.com/problems/smallest-number-with-all-set-bits/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive number n.
//
// Return the smallest number x greater than or equal to n, such that the binary representation of x contains only set bits
//
// Example:
// Input: n = 5
//
// Output: 7
//
// Explanation:
//
// The binary representation of 7 is "111".
//
// Constraints:
// 1 <= n <= 1000
//

int smallestNumber(int n) {
    int x = 1;
    while (x < n) {
        x = (x << 1) | 1;
    }
    return x;       
}
