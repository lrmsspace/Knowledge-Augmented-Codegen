// Source: https://leetcode.com/problems/maximum-odd-binary-number/   |   Difficulty: Easy
//
// Problem Description:
// You are given a binary string s that contains at least one '1'.
//
// You have to rearrange the bits in such a way that the resulting binary number is the maximum odd binary number that can be created from this combination.
//
// Return a string representing the maximum odd binary number that can be created from the given combination.
//
// Note that the resulting string can have leading zeros.
//
// Example:
// Input: s = "010"
// Output: "001"
// Explanation: Because there is just one '1', it must be in the last position. So the answer is "001".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of '0' and '1'.
// 	s contains at least one '1'.
//

class Solution {
    public String maximumOddBinaryNumber(String s) {
        int countZero = 0;
        int countOne = 0;

        for (char c : s.toCharArray()) {
            if (c == '0') {
                countZero++;
            } else {
                countOne++;
            }
        }

        StringBuilder sb = new StringBuilder();

        // Append all '1's except one
        for (int i = 0; i < countOne - 1; i++) {
            sb.append('1');
        }

        // Append all '0's
        for (int i = 0; i < countZero; i++) {
            sb.append('0');
        }

        // Append the last '1' to make the number odd
        sb.append('1');

        return sb.toString();           
    }
}
