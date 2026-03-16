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

int minPartitions(char* n) {
    int max_digit = 0;
    for (int i = 0; n[i] != '\0'; i++) {
        int digit = n[i] - '0';
        if (digit > max_digit) {
            max_digit = digit;
        }
        if (max_digit == 9) {
            break; // Early exit since 9 is the maximum possible digit
        }
    }
    return max_digit;       
}
