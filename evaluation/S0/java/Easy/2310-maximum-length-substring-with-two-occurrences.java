// Source: https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the maximum length of a substring such that it contains at most two occurrences of each character.
//
// Example:
// Input: s = "bcbbbcba"
//
// Output: 4
//
// Explanation:
// The following substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists only of lowercase English letters.
//

class Solution {
    public int maximumLengthSubstring(String s) {
        int maxLength = 0;

        for (int start = 0; start < s.length(); start++) {
            int[] charCount = new int[26];
            int currentLength = 0;

            for (int end = start; end < s.length(); end++) {
                char currentChar = s.charAt(end);
                charCount[currentChar - 'a']++;

                if (charCount[currentChar - 'a'] > 2) {
                    break;
                }

                currentLength++;
                maxLength = Math.max(maxLength, currentLength);
            }
        }

        return maxLength;           
    }
}
