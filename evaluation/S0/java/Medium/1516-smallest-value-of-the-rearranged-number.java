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
    public long smallestNumber(long num) {
        if (num == 0) return 0;

        boolean isNegative = num < 0;
        String numStr = Long.toString(Math.abs(num));
        char[] digits = numStr.toCharArray();
        Arrays.sort(digits);

        StringBuilder result = new StringBuilder();

        if (isNegative) {
            // For negative numbers, we want the largest arrangement
            for (int i = digits.length - 1; i >= 0; i--) {
                result.append(digits[i]);
            }
            return -Long.parseLong(result.toString());
        } else {
            // For positive numbers, we want the smallest arrangement without leading zeros
            if (digits[0] == '0') {
                // Find the first non-zero digit
                int nonZeroIndex = 1;
                while (nonZeroIndex < digits.length && digits[nonZeroIndex] == '0') {
                    nonZeroIndex++;
                }
                // Swap the first non-zero digit with the leading zero
                if (nonZeroIndex < digits.length) {
                    char temp = digits[0];
                    digits[0] = digits[nonZeroIndex];
                    digits[nonZeroIndex] = temp;
                }
            }
            for (char digit : digits) {
                result.append(digit);
            }
            return Long.parseLong(result.toString());
        }           
    }
}
