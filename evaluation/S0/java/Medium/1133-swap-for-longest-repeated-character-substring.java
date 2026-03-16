// Source: https://leetcode.com/problems/swap-for-longest-repeated-character-substring/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string text. You can swap two of the characters in the text.
//
// Return the length of the longest substring with repeated characters.
//
// Example:
// Input: text = "ababa"
// Output: 3
// Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa" with length 3.
//
// Constraints:
// 1 <= text.length <= 2 * 104
// 	text consist of lowercase English characters only.
//

class Solution {
    public int maxRepOpt1(String text) {
        int n = text.length();
        int[] count = new int[26];
        for (char c : text.toCharArray()) {
            count[c - 'a']++;
        }

        int maxLen = 0;
        for (int i = 0; i < n; ) {
            char currChar = text.charAt(i);
            int j = i;
            while (j < n && text.charAt(j) == currChar) {
                j++;
            }
            int len1 = j - i;

            int k = j + 1;
            while (k < n && text.charAt(k) == currChar) {
                k++;
            }
            int len2 = k - j - 1;

            int totalLen = len1 + len2 < count[currChar - 'a'] ? len1 + len2 + 1 : len1 + len2;
            maxLen = Math.max(maxLen, totalLen);

            i = j;
        }

        return maxLen;          
    }
}
