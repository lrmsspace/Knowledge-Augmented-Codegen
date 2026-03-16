// Source: https://leetcode.com/problems/number-of-digit-one/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
//
// Example:
// Input: n = 13
// Output: 6
//
// Constraints:
// 0 <= n <= 109
//

class Solution {
    public int countDigitOne(int n) {
        int count = 0;
        for (long i = 1; i <= n; i *= 10) {
            long divider = i * 10;
            count += (n / divider) * i + Math.min(Math.max(n % divider - i + 1, 0), i);
        }
        return count;           
    }
}
