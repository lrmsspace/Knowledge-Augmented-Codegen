// Source: https://leetcode.com/problems/count-special-integers/   |   Difficulty: Hard
//
// Problem Description:
// We call a positive integer special if all of its digits are distinct.
//
// Given a positive integer n, return the number of special integers that belong to the interval [1, n].
//
// Example:
// Input: n = 20
// Output: 19
// Explanation: All the integers from 1 to 20, except 11, are special. Thus, there are 19 special integers.
//
// Constraints:
// 1 <= n <= 2 * 109
//

class Solution {
    public int countSpecialNumbers(int n) {
        String s = Integer.toString(n);
        int m = s.length();
        int res = 0;

        // Count special numbers with fewer digits than n
        for (int i = 1; i < m; i++) {
            res += 9 * perm(9, i - 1);
        }

        // Count special numbers with the same number of digits as n
        boolean[] used = new boolean[10];
        for (int i = 0; i < m; i++) {
            int digit = s.charAt(i) - '0';
            for (int d = (i == 0 ? 1 : 0); d < digit; d++) {
                if (!used[d]) {
                    res += perm(10 - (i + 1), m - (i + 1));
                }
            }
            if (used[digit]) {
                return res;
            }
            used[digit] = true;
        }
        return res + 1; // Include n itself if it's special         
    }
}
