// Source: https://leetcode.com/problems/super-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// Let's say a positive integer is a super-palindrome if it is a palindrome, and it is also the square of a palindrome.
//
// Given two positive integers left and right represented as strings, return the number of super-palindromes integers in the inclusive range [left, right].
//
// Example:
// Input: left = "4", right = "1000"
// Output: 4
// Explanation: 4, 9, 121, and 484 are superpalindromes.
// Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.
//
// Constraints:
// 1 <= left.length, right.length <= 18
// 	left and right consist of only digits.
// 	left and right cannot have leading zeros.
// 	left and right represent integers in the range [1, 1018 - 1].
// 	left is less than or equal to right.
//

class Solution {
    public int superpalindromesInRange(String left, String right) {
        long l = Long.parseLong(left);
        long r = Long.parseLong(right);
        int count = 0;

        // Generate palindromic roots and check their squares
        for (int k = 1; k < 100000; k++) {
            StringBuilder sb = new StringBuilder(Integer.toString(k));
            // Odd-length palindromes
            String oddPalindromeStr = sb.toString() + sb.reverse().substring(1);
            long oddPalindrome = Long.parseLong(oddPalindromeStr);
            long oddSquare = oddPalindrome * oddPalindrome;
            if (oddSquare > r) break;
            if (oddSquare >= l && isPalindrome(oddSquare)) {
                count++;
            }

            // Even-length palindromes
            sb = new StringBuilder(Integer.toString(k));
            String evenPalindromeStr = sb.toString() + sb.reverse().toString();
            long evenPalindrome = Long.parseLong(evenPalindromeStr);
            long evenSquare = evenPalindrome * evenPalindrome;
            if (evenSquare > r) continue;
            if (evenSquare >= l && isPalindrome(evenSquare)) {
                count++;
            }
        }

        return count;           
    }
}
