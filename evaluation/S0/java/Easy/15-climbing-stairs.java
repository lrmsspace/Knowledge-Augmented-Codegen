// Source: https://leetcode.com/problems/climbing-stairs/   |   Difficulty: Easy
//
// Problem Description:
// You are climbing a staircase. It takes n steps to reach the top.
//
// Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
//
// Example:
// Input: n = 2
// Output: 2
// Explanation: There are two ways to climb to the top.
// 1. 1 step + 1 step
// 2. 2 steps
//
// Constraints:
// 1 <= n <= 45
//

class Solution {
    public int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }

        int first = 1;
        int second = 2;
        int third = 0;

        for (int i = 3; i <= n; i++) {
            third = first + second;
            first = second;
            second = third;
        }

        return third;           
    }
}
