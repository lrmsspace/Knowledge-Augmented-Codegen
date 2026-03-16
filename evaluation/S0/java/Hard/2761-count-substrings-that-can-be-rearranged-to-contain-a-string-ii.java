// Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called valid if x can be rearranged to have word2 as a prefix.
//
// Return the total number of valid substrings of word1.
//
// Note that the memory limits in this problem are smaller than usual, so you must implement a solution with a linear runtime complexity.
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
// 1 <= word1.length <= 106
// 	1 <= word2.length <= 104
// 	word1 and word2 consist only of lowercase English letters.
//

class Solution {
    public long validSubstringCount(String word1, String word2) {
        int n = word1.length(), m = word2.length();
        int[] count = new int[26];
        for (char c : word2.toCharArray()) {
            count[c - 'a']++;
        }

        long result = 0;
        int left = 0, right = 0, required = m;

        while (right < n) {
            char rightChar = word1.charAt(right);
            if (count[rightChar - 'a'] > 0) {
                required--;
            }
            count[rightChar - 'a']--;
            right++;

            while (required == 0) {
                result += n - right + 1;

                char leftChar = word1.charAt(left);
                count[leftChar - 'a']++;
                if (count[leftChar - 'a'] > 0) {
                    required++;
                }
                left++;
            }
        }

        return result;          
    }
}
