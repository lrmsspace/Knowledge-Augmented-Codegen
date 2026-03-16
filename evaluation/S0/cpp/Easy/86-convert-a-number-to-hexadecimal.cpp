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
public:
    string toHex(int num) {
        if (num == 0) return "0";
        
        const char* hexChars = "0123456789abcdef";
        unsigned int n = static_cast<unsigned int>(num);
        string result;
        
        while (n > 0) {
            int remainder = n % 16;
            result = hexChars[remainder] + result;
            n /= 16;
        }
        
        return result;          
    }
};
