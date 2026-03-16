// Source: https://leetcode.com/problems/count-vowel-substrings-of-a-string/   |   Difficulty: Easy
//
// Problem Description:
// A substring is a contiguous (non-empty) sequence of characters within a string.
//
// A vowel substring is a substring that only consists of vowels ('a', 'e', 'i', 'o', and 'u') and has all five vowels present in it.
//
// Given a string word, return the number of vowel substrings in word.
//
// Example:
// Input: word = "aeiouu"
// Output: 2
// Explanation: The vowel substrings of word are as follows (underlined):
// - "aeiouu"
// - "aeiouu"
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists of lowercase English letters only.
//

class Solution {
    public int countVowelSubstrings(String word) {
        int count = 0;
        int n = word.length();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                String substring = word.substring(i, j);
                if (isVowelSubstring(substring)) {
                    count++;
                }
            }
        }
        return count;           
    }
}
