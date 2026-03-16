// Source: https://leetcode.com/problems/rotated-digits/   |   Difficulty: Medium
//
// Problem Description:
// An integer x is a good if after rotating each digit individually by 180 degrees, we get a valid number that is different from x. Each digit must be rotated - we cannot choose to leave it alone.
//
// A number is valid if each digit remains a digit after rotation. For example:
//
//
// 	0, 1, and 8 rotate to themselves,
// 	2 and 5 rotate to each other (in this case they are rotated in a different direction, in other words, 2 or 5 gets mirrored),
// 	6 and 9 rotate to each other, and
// 	the rest of the numbers do not rotate to any other number and become invalid.
//
//
// Given an integer n, return the number of good integers in the range [1, n].
//
// Example:
// Input: n = 10
// Output: 4
// Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
// Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
//
// Constraints:
// 1 <= n <= 104
//

class Solution {
public:
    int rotatedDigits(int n) {
        int goodCount = 0;

        for (int num = 1; num <= n; ++num) {
            bool isGood = false;
            int current = num;

            while (current > 0) {
                int digit = current % 10;
                current /= 10;

                if (digit == 3 || digit == 4 || digit == 7) {
                    isGood = false;
                    break;
                }
                if (digit == 2 || digit == 5 || digit == 6 || digit == 9) {
                    isGood = true;
                }
            }

            if (isGood) {
                ++goodCount;
            }
        }

        return goodCount;           
    }
};
