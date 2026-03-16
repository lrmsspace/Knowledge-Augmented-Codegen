// Source: https://leetcode.com/problems/largest-multiple-of-three/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of digits digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order. If there is no answer return an empty string.
//
// Since the answer may not fit in an integer data type, return the answer as a string. Note that the returning answer must not contain unnecessary leading zeros.
//
// Example:
// Input: digits = [8,1,9]
// Output: "981"
//
// Constraints:
// 1 <= digits.length <= 104
// 	0 <= digits[i] <= 9
//

class Solution {
    public String largestMultipleOfThree(int[] digits) {
        int[] count = new int[10];
        int sum = 0;
        for (int digit : digits) {
            count[digit]++;
            sum += digit;
        }

        int mod = sum % 3;
        if (mod != 0) {
            if (!removeDigits(count, mod, 1)) {
                int otherMod = 3 - mod;
                if (!removeDigits(count, otherMod, 2)) {
                    return "";
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 9; i >= 0; i--) {
            while (count[i] > 0) {
                sb.append(i);
                count[i]--;
            }
        }

        if (sb.length() > 0 && sb.charAt(0) == '0') {
            return "0";
        }

        return sb.toString();                   
    }
}
