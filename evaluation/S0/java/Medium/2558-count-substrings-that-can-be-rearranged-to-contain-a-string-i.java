// Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called valid if x can be rearranged to have word2 as a prefix.
//
// Return the total number of valid substrings of word1.
//
// Example:
// Input: word1 = "bcca", word2 = "abc"
//
// Output: 1
//
// Explanation:
//
// The only valid substring is "bcca" which can be rearranged to "abcc" having "abc" as a prefix.
//
// Constraints:
// 1 <= word1.length <= 105
// 	1 <= word2.length <= 104
// 	word1 and word2 consist only of lowercase English letters.
//

class Solution {
    public long validSubstringCount(String word1, String word2) {
        int n = word1.length();
        int m = word2.length();

        int[] countWord2 = new int[26];
        for (char c : word2.toCharArray()) {
            countWord2[c - 'a']++;
        }

        long result = 0;
        int[] windowCount = new int[26];
        int left = 0;

        for (int right = 0; right < n; right++) {
            windowCount[word1.charAt(right) - 'a']++;

            while (!canFormPrefix(windowCount, countWord2)) {
                windowCount[word1.charAt(left) - 'a']--;
                left++;
            }

            result += (right - left + 1);
        }

        return result;          
    }
}
