// Source: https://leetcode.com/problems/base-7/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer num, return a string of its base 7 representation.
//
// Example:
// Input: num = 100
// Output: "202"
//
// Constraints:
// -107 <= num <= 107
//

class Solution {
public:
    string convertToBase7(int num) {
        if (num == 0) return "0";
        
        bool isNegative = num < 0;
        num = abs(num);
        string base7 = "";
        
        while (num > 0) {
            base7 = to_string(num % 7) + base7;
            num /= 7;
        }
        
        if (isNegative) {
            base7 = "-" + base7;
        }
        
        return base7;           
    }
};
