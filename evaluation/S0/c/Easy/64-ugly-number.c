// Source: https://leetcode.com/problems/ugly-number/   |   Difficulty: Easy
//
// Problem Description:
// An ugly number is a positive integer which does not have a prime factor other than 2, 3, and 5.
//
// Given an integer n, return true if n is an ugly number.
//
// Example:
// Input: n = 6
// Output: true
// Explanation: 6 = 2 × 3
//
// Constraints:
// -231 <= n <= 231 - 1
//

bool isUgly(int n) {
    if (n <= 0) {
        return false;
    }
    
    while (n % 2 == 0) {
        n /= 2;
    }
    
    while (n % 3 == 0) {
        n /= 3;
    }
    
    while (n % 5 == 0) {
        n /= 5;
    }
    
    return n == 1;      
}
