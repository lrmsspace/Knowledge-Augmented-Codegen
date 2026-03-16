// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a palindromic string s.
//
// Return the lexicographically smallest palindromic permutation of s.
//
// Example:
// Input: s = "z"
//
// Output: "z"
//
// Explanation:
//
// A string of only one character is already the lexicographically smallest palindrome.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
//

class Solution {
    public String smallestPalindrome(String s) {
        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }

        StringBuilder half = new StringBuilder();
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < count[i] / 2; j++) {
                half.append((char) (i + 'a'));
            }
        }

        String halfStr = half.toString();
        StringBuilder result = new StringBuilder(halfStr);
        if (s.length() % 2 == 1) {
            for (int i = 0; i < 26; i++) {
                if (count[i] % 2 == 1) {
                    result.append((char) (i + 'a'));
                    break;
                }
            }
        }
        result.append(new StringBuilder(halfStr).reverse());
        return result.toString();           
    }
}
