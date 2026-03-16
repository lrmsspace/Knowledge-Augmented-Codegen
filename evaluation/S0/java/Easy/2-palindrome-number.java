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
    public boolean isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int revertedNumber = 0;
        while (x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }

        return x == revertedNumber || x == revertedNumber / 10;         
    }
}
