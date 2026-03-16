// Source: https://leetcode.com/problems/longest-substring-without-repeating-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find the length of the longest substring without duplicate characters.
//
// Example:
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
//
// Constraints:
// 0 <= s.length <= 5 * 104
// 	s consists of English letters, digits, symbols and spaces.
//

class Solution {
    public int lengthOfLongestSubstring(String s) {
        int n = s.length();
        int maxLength = 0;
        int left = 0;
        Map<Character, Integer> charIndexMap = new HashMap<>();

        for (int right = 0; right < n; right++) {
            char currentChar = s.charAt(right);

            if (charIndexMap.containsKey(currentChar)) {
                left = Math.max(charIndexMap.get(currentChar) + 1, left);
            }

            charIndexMap.put(currentChar, right);
            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;           
    }
}
