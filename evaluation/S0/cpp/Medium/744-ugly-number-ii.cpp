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
public:
    int nthUglyNumber(int n) {
        vector<int> uglyNumbers(n);
        uglyNumbers[0] = 1;

        int i2 = 0, i3 = 0, i5 = 0;
        for (int i = 1; i < n; ++i) {
            int next2 = uglyNumbers[i2] * 2;
            int next3 = uglyNumbers[i3] * 3;
            int next5 = uglyNumbers[i5] * 5;

            int nextUgly = min(next2, min(next3, next5));
            uglyNumbers[i] = nextUgly;

            if (nextUgly == next2) ++i2;
            if (nextUgly == next3) ++i3;
            if (nextUgly == next5) ++i5;
        }

        return uglyNumbers[n - 1];          
    }
};
