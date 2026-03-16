// Source: https://leetcode.com/problems/numbers-at-most-n-given-digit-set/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of digits which is sorted in non-decreasing order. You can write numbers using each digits[i] as many times as we want. For example, if digits = ['1','3','5'], we may write numbers such as '13', '551', and '1351315'.
//
// Return the number of positive integers that can be generated that are less than or equal to a given integer n.
//
// Example:
// Input: digits = ["1","3","5","7"], n = 100
// Output: 20
// Explanation: 
// The 20 numbers that can be written are:
// 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
//
// Constraints:
// 1 <= digits.length <= 9
// 	digits[i].length == 1
// 	digits[i] is a digit from '1' to '9'.
// 	All the values in digits are unique.
// 	digits is sorted in non-decreasing order.
// 	1 <= n <= 109
//

class Solution {
    public int atMostNGivenDigitSet(String[] digits, int n) {
        String nStr = Integer.toString(n);
        int nLen = nStr.length();
        int dLen = digits.length;
        int total = 0;

        // Count numbers with fewer digits than n
        for (int len = 1; len < nLen; len++) {
            total += Math.pow(dLen, len);
        }

        // Count numbers with the same number of digits as n
        for (int i = 0; i < nLen; i++) {
            boolean hasSameDigit = false;
            for (String digit : digits) {
                if (digit.charAt(0) < nStr.charAt(i)) {
                    total += Math.pow(dLen, nLen - i - 1);
                } else if (digit.charAt(0) == nStr.charAt(i)) {
                    hasSameDigit = true;
                    break;
                }
            }
            if (!hasSameDigit) {
                return total;
            }
        }

        // Include n itself if all digits matched
        return total + 1;           
    }
}
