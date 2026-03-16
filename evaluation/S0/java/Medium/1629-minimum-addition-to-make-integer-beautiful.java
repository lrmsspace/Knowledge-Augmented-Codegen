// Source: https://leetcode.com/problems/minimum-addition-to-make-integer-beautiful/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers n and target.
//
// An integer is considered beautiful if the sum of its digits is less than or equal to target.
//
// Return the minimum non-negative integer x such that n + x is beautiful. The input will be generated such that it is always possible to make n beautiful.
//
// Example:
// Input: n = 16, target = 6
// Output: 4
// Explanation: Initially n is 16 and its digit sum is 1 + 6 = 7. After adding 4, n becomes 20 and digit sum becomes 2 + 0 = 2. It can be shown that we can not make n beautiful with adding non-negative integer less than 4.
//
// Constraints:
// 1 <= n <= 1012
// 	1 <= target <= 150
// 	The input will be generated such that it is always possible to make n beautiful.
//

class Solution {
    public long makeIntegerBeautiful(long n, int target) {
        long addition = 0;
        long place = 1;

        while (digitSum(n) > target) {
            long digit = (n / place) % 10;
            long increment = (10 - digit) % 10;

            addition += increment * place;
            n += increment * place;
            place *= 10;
        }

        return addition;            
    }
}
