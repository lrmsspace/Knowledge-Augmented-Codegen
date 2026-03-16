// Source: https://leetcode.com/problems/additive-number/   |   Difficulty: Medium
//
// Problem Description:
// An additive number is a string whose digits can form an additive sequence.
//
// A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.
//
// Given a string containing only digits, return true if it is an additive number or false otherwise.
//
// Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.
//
// Example:
// Input: "112358"
// Output: true
// Explanation: 
// The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
// 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
//
// Constraints:
// 1 <= num.length <= 35
// 	num consists only of digits.
//
//
//  
// Follow up: How would you handle overflow for very large input integers?
//

class Solution {
    public boolean isAdditiveNumber(String num) {
        int n = num.length();
        for (int i = 1; i <= n / 2; i++) {
            for (int j = 1; Math.max(i, j) <= n - i - j; j++) {
                if (isValid(i, j, num)) {
                    return true;
                }
            }
        }
        return false;           
    }
}
