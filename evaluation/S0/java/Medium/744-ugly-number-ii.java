// Source: https://leetcode.com/problems/ugly-number-ii/   |   Difficulty: Medium
//
// Problem Description:
// An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
//
// Given an integer n, return the nth ugly number.
//
// Example:
// Input: n = 10
// Output: 12
// Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.
//
// Constraints:
// 1 <= n <= 1690
//

class Solution {
    public int nthUglyNumber(int n) {
        int[] uglyNumbers = new int[n];
        uglyNumbers[0] = 1;

        int index2 = 0, index3 = 0, index5 = 0;

        for (int i = 1; i < n; i++) {
            int next2 = uglyNumbers[index2] * 2;
            int next3 = uglyNumbers[index3] * 3;
            int next5 = uglyNumbers[index5] * 5;

            int nextUgly = Math.min(next2, Math.min(next3, next5));
            uglyNumbers[i] = nextUgly;

            if (nextUgly == next2) index2++;
            if (nextUgly == next3) index3++;
            if (nextUgly == next5) index5++;
        }

        return uglyNumbers[n - 1];          
    }
}
