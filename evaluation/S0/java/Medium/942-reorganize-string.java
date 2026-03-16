// Source: https://leetcode.com/problems/reorganize-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.
//
// Return any possible rearrangement of s or return "" if not possible.
//
// Example:
// Input: s = "aab"
// Output: "aba"
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of lowercase English letters.
//

class Solution {
    public String reorganizeString(String s) {
        int n = s.length();
        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }

        int maxCount = 0;
        int maxCharIndex = 0;
        for (int i = 0; i < 26; i++) {
            if (count[i] > maxCount) {
                maxCount = count[i];
                maxCharIndex = i;
            }
        }

        if (maxCount > (n + 1) / 2) {
            return "";
        }

        char[] result = new char[n];
        int index = 0;

        while (count[maxCharIndex] > 0) {
            result[index] = (char) (maxCharIndex + 'a');
            index += 2;
            count[maxCharIndex]--;
        }

        for (int i = 0; i < 26; i++) {
            while (count[i] > 0) {
                if (index >= n) {
                    index = 1;
                }
                result[index] = (char) (i + 'a');
                index += 2;
                count[i]--;
            }
        }

        return new String(result);          
    }
}
