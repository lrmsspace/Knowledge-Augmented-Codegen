// Source: https://leetcode.com/problems/longest-palindrome/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.
//
// Letters are case sensitive, for example, "Aa" is not considered a palindrome.
//
// Example:
// Input: s = "abccccdd"
// Output: 7
// Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.
//
// Constraints:
// 1 <= s.length <= 2000
// 	s consists of lowercase and/or uppercase English letters only.
//

class Solution {
    public int longestPalindrome(String s) {
        int[] charCounts = new int[128];
        for (char c : s.toCharArray()) {
            charCounts[c]++;
        }

        int length = 0;
        boolean hasOddCount = false;

        for (int count : charCounts) {
            if (count % 2 == 0) {
                length += count;
            } else {
                length += count - 1;
                hasOddCount = true;
            }
        }

        if (hasOddCount) {
            length += 1;
        }

        return length;          
    }
}
