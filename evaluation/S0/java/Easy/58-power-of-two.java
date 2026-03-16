// Source: https://leetcode.com/problems/power-of-two/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if it is a power of two. Otherwise, return false.
//
// An integer n is a power of two, if there exists an integer x such that n == 2x.
//
// Example:
// Input: n = 1
// Output: true
// Explanation: 20 = 1
//
// Constraints:
// -231 <= n <= 231 - 1
//
//
//  
// Follow up: Could you solve it without loops/recursion?
//

class Solution {
    public boolean isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;         
    }
}
