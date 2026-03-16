// Source: https://leetcode.com/problems/valid-perfect-square/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num, return true if num is a perfect square or false otherwise.
//
// A perfect square is an integer that is the square of an integer. In other words, it is the product of some integer with itself.
//
// You must not use any built-in library function, such as sqrt.
//
// Example:
// Input: num = 16
// Output: true
// Explanation: We return true because 4 * 4 = 16 and 4 is an integer.
//
// Constraints:
// 1 <= num <= 231 - 1
//

class Solution {
    public boolean isPerfectSquare(int num) {
        if (num == 1) {
            return true;
        }

        long left = 1;
        long right = num / 2;

        while (left <= right) {
            long mid = left + (right - left) / 2;
            long square = mid * mid;

            if (square == num) {
                return true;
            } else if (square < num) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return false;           
    }
}
