// Source: https://leetcode.com/problems/sum-of-square-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 = c.
//
// Example:
// Input: c = 5
// Output: true
// Explanation: 1 * 1 + 2 * 2 = 5
//
// Constraints:
// 0 <= c <= 231 - 1
//

class Solution {
    public boolean judgeSquareSum(int c) {
        int left = 0;
        int right = (int) Math.sqrt(c);

        while (left <= right) {
            int sum = left * left + right * right;
            if (sum == c) {
                return true;
            } else if (sum < c) {
                left++;
            } else {
                right--;
            }
        }

        return false;           
    }
}
