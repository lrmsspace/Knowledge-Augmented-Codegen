// Source: https://leetcode.com/problems/nth-digit/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the nth digit of the infinite integer sequence [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].
//
// Example:
// Input: n = 3
// Output: 3
//
// Constraints:
// 1 <= n <= 231 - 1
//

class Solution {
    public int findNthDigit(int n) {
        int digitLength = 1;
        long count = 9;
        long start = 1;

        // Find the range where the nth digit is located
        while (n > digitLength * count) {
            n -= digitLength * count;
            digitLength++;
            count *= 10;
            start *= 10;
        }

        // Find the actual number that contains the nth digit
        start += (n - 1) / digitLength;
        String s = Long.toString(start);

        // Find the specific digit in that number
        return Character.getNumericValue(s.charAt((n - 1) % digitLength));          
    }
}
