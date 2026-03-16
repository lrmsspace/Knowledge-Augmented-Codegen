// Source: https://leetcode.com/problems/break-a-palindrome/   |   Difficulty: Medium
//
// Problem Description:
// Given a palindromic string of lowercase English letters palindrome, replace exactly one character with any lowercase English letter so that the resulting string is not a palindrome and that it is the lexicographically smallest one possible.
//
// Return the resulting string. If there is no way to replace a character to make it not a palindrome, return an empty string.
//
// A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, a has a character strictly smaller than the corresponding character in b. For example, "abcc" is lexicographically smaller than "abcd" because the first position they differ is at the fourth character, and 'c' is smaller than 'd'.
//
// Example:
// Input: palindrome = "abccba"
// Output: "aaccba"
// Explanation: There are many ways to make "abccba" not a palindrome, such as "zbccba", "aaccba", and "abacba".
// Of all the ways, "aaccba" is the lexicographically smallest.
//
// Constraints:
// 1 <= palindrome.length <= 1000
// 	palindrome consists of only lowercase English letters.
//

class Solution {
    public String breakPalindrome(String palindrome) {
        int n = palindrome.length();
        if (n == 1) {
            return "";
        }

        char[] chars = palindrome.toCharArray();
        for (int i = 0; i < n / 2; i++) {
            if (chars[i] != 'a') {
                chars[i] = 'a';
                return new String(chars);
            }
        }

        chars[n - 1] = 'b';
        return new String(chars);           
    }
}
