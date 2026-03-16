// Source: https://leetcode.com/problems/count-symmetric-integers/   |   Difficulty: Easy
//
// Problem Description:
// You are given two positive integers low and high.
//
// An integer x consisting of 2 * n digits is symmetric if the sum of the first n digits of x is equal to the sum of the last n digits of x. Numbers with an odd number of digits are never symmetric.
//
// Return the number of symmetric integers in the range [low, high].
//
// Example:
// Input: low = 1, high = 100
// Output: 9
// Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.
//
// Constraints:
// 1 <= low <= high <= 104
//

class Solution {
    public int countSymmetricIntegers(int low, int high) {
        int count = 0;

        for (int num = low; num <= high; num++) {
            String strNum = Integer.toString(num);
            int length = strNum.length();

            if (length % 2 != 0) {
                continue; // Skip numbers with odd number of digits
            }

            int mid = length / 2;
            int sumFirstHalf = 0;
            int sumSecondHalf = 0;

            for (int i = 0; i < mid; i++) {
                sumFirstHalf += strNum.charAt(i) - '0';
                sumSecondHalf += strNum.charAt(i + mid) - '0';
            }

            if (sumFirstHalf == sumSecondHalf) {
                count++;
            }
        }

        return count;           
    }
}
