// Source: https://leetcode.com/problems/power-of-three/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if it is a power of three. Otherwise, return false.
//
// An integer n is a power of three, if there exists an integer x such that n == 3x.
//
// Example:
// Input: n = 27
// Output: true
// Explanation: 27 = 33
//
// Constraints:
// -231 <= n <= 231 - 1
//
//
//  
// Follow up: Could you solve it without loops/recursion?
//

bool isPowerOfThree(int n) {
    if (n < 1) {
        return false;
    }
    while (n % 3 == 0) {
        n /= 3;
    }
    return n == 1;      
}
