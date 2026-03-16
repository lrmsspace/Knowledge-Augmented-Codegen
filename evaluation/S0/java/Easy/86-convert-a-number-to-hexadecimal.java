// Source: https://leetcode.com/problems/convert-a-number-to-hexadecimal/   |   Difficulty: Easy
//
// Problem Description:
// Given a 32-bit integer num, return a string representing its hexadecimal representation. For negative integers, two’s complement method is used.
//
// All the letters in the answer string should be lowercase characters, and there should not be any leading zeros in the answer except for the zero itself.
//
// Note: You are not allowed to use any built-in library method to directly solve this problem.
//
// Example:
// Input: num = 26
// Output: "1a"
//
// Constraints:
// -231 <= num <= 231 - 1
//

class Solution {
    public String toHex(int num) {
        if (num == 0) return "0";
        
        char[] hexChars = "0123456789abcdef".toCharArray();
        StringBuilder hexString = new StringBuilder();
        
        // Use a mask to get the last 4 bits and convert to hex
        for (int i = 0; i < 8 && num != 0; i++) {
            int hexDigit = num & 0xF; // Get the last 4 bits
            hexString.append(hexChars[hexDigit]);
            num >>>= 4; // Logical right shift by 4 bits
        }
        
        return hexString.reverse().toString();          
    }
}
