// Source: https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/   |   Difficulty: Medium
//
// Problem Description:
// A decimal number is called deci-binary if each of its digits is either 0 or 1 without any leading zeros. For example, 101 and 1100 are deci-binary, while 112 and 3001 are not.
//
// Given a string n that represents a positive decimal integer, return the minimum number of positive deci-binary numbers needed so that they sum up to n.
//
// Example:
// Input: n = "32"
// Output: 3
// Explanation: 10 + 11 + 11 = 32
//
// Constraints:
// 1 <= n.length <= 105
// 	n consists of only digits.
// 	n does not contain any leading zeros and represents a positive integer.
//

class Solution {
    public int minPartitions(String n) {
        int maxDigit = 0;
        for (char c : n.toCharArray()) {
            int digit = c - '0';
            if (digit > maxDigit) {
                maxDigit = digit;
            }
            if (maxDigit == 9) {
                break; // Early exit since 9 is the maximum possible digit
            }
        }
        return maxDigit;            
    }
}
