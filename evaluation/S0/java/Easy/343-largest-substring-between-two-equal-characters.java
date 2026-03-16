// Source: https://leetcode.com/problems/largest-substring-between-two-equal-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "aa"
// Output: 0
// Explanation: The optimal substring here is an empty substring between the two 'a's.
//
// Constraints:
// 1 <= s.length <= 300
// 	s contains only lowercase English letters.
//

class Solution {
    public int maxLengthBetweenEqualCharacters(String s) {
        int maxLength = -1;
        int[] firstOccurrence = new int[26];

        for (int i = 0; i < 26; i++) {
            firstOccurrence[i] = -1;
        }

        for (int i = 0; i < s.length(); i++) {
            int charIndex = s.charAt(i) - 'a';

            if (firstOccurrence[charIndex] == -1) {
                firstOccurrence[charIndex] = i;
            } else {
                int currentLength = i - firstOccurrence[charIndex] - 1;
                maxLength = Math.max(maxLength, currentLength);
            }
        }

        return maxLength;           
    }
}
