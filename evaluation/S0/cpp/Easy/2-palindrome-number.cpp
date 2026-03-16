// Source: https://leetcode.com/problems/palindrome-number/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer x, return true if x is a palindrome, and false otherwise.
//
// Example:
// Input: x = 121
// Output: true
// Explanation: 121 reads as 121 from left to right and from right to left.
//
// Constraints:
// -231 <= x <= 231 - 1
//
//
//  
// Follow up: Could you solve it without converting the integer to a string?
//

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int div = 1;
        while (x / div >= 10) {
            div *= 10;
        }
        while (x != 0) {
            int left = x / div;
            int right = x % 10;
            if (left != right) return false;
            x = (x % div) / 10;
            div /= 100;
        }
        return true;            
    }
};
