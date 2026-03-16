// Source: https://leetcode.com/problems/smallest-value-of-the-rearranged-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. Rearrange the digits of num such that its value is minimized and it does not contain any leading zeros.
//
// Return the rearranged number with minimal value.
//
// Note that the sign of the number does not change after rearranging the digits.
//
// Example:
// Input: num = 310
// Output: 103
// Explanation: The possible arrangements for the digits of 310 are 013, 031, 103, 130, 301, 310. 
// The arrangement with the smallest value that does not contain any leading zeros is 103.
//
// Constraints:
// -1015 <= num <= 1015
//

long long smallestNumber(long long num) {
    int is_negative = num < 0 ? 1 : 0;
    if (is_negative) {
        num = -num;
    }

    int digit_count[10] = {0};
    while (num > 0) {
        int digit = num % 10;
        digit_count[digit]++;
        num /= 10;
    }

    long long result = 0;
    if (is_negative) {
        for (int digit = 9; digit >= 0; digit--) {
            while (digit_count[digit] > 0) {
                result = result * 10 + digit;
                digit_count[digit]--;
            }
        }
        result = -result;
    } else {
        for (int digit = 1; digit <= 9; digit++) {
            if (digit_count[digit] > 0) {
                result = digit;
                digit_count[digit]--;
                break;
            }
        }
        for (int digit = 0; digit <= 9; digit++) {
            while (digit_count[digit] > 0) {
                result = result * 10 + digit;
                digit_count[digit]--;
            }
        }
    }

    return result;      
}
