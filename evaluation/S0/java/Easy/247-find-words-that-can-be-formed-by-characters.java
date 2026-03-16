// Source: https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of strings words and a string chars.
//
// A string is good if it can be formed by characters from chars (each character can only be used once for each word in words).
//
// Return the sum of lengths of all good strings in words.
//
// Example:
// Input: words = ["cat","bt","hat","tree"], chars = "atach"
// Output: 6
// Explanation: The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length, chars.length <= 100
// 	words[i] and chars consist of lowercase English letters.
//

class Solution {
    public int countCharacters(String[] words, String chars) {
        int[] charCount = new int[26];
        for (char c : chars.toCharArray()) {
            charCount[c - 'a']++;
        }

        int totalLength = 0;

        for (String word : words) {
            int[] wordCount = new int[26];
            for (char c : word.toCharArray()) {
                wordCount[c - 'a']++;
            }

            boolean canFormWord = true;
            for (int i = 0; i < 26; i++) {
                if (wordCount[i] > charCount[i]) {
                    canFormWord = false;
                    break;
                }
            }

            if (canFormWord) {
                totalLength += word.length();
            }
        }

        return totalLength;         
    }
}
