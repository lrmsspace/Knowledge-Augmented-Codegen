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

class Solution {
public:
    long long smallestNumber(long long num) {
        if (num == 0) return 0;

        bool isNegative = num < 0;
        string numStr = to_string(isNegative ? -num : num);
        vector<int> digitCount(10, 0);

        for (char digit : numStr) {
            digitCount[digit - '0']++;
        }

        string result;
        if (isNegative) {
            // For negative numbers, arrange digits in descending order
            for (int digit = 9; digit >= 0; --digit) {
                result.append(digitCount[digit], '0' + digit);
            }
            return -stoll(result);
        } else {
            // For positive numbers, arrange digits in ascending order
            // Find the first non-zero digit
            for (int digit = 1; digit <= 9; ++digit) {
                if (digitCount[digit] > 0) {
                    result += ('0' + digit);
                    digitCount[digit]--;
                    break;
                }
            }
            // Append remaining digits including zeros
            for (int digit = 0; digit <= 9; ++digit) {
                result.append(digitCount[digit], '0' + digit);
            }
            return stoll(result);
        }           
    }
};
