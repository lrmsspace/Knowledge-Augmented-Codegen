// Source: https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/   |   Difficulty: Easy
//
// Problem Description:
// Given a sentence that consists of some words separated by a single space, and a searchWord, check if searchWord is a prefix of any word in sentence.
//
// Return the index of the word in sentence (1-indexed) where searchWord is a prefix of this word. If searchWord is a prefix of more than one word, return the index of the first word (minimum index). If there is no such word return -1.
//
// A prefix of a string s is any leading contiguous substring of s.
//
// Example:
// Input: sentence = "i love eating burger", searchWord = "burg"
// Output: 4
// Explanation: "burg" is prefix of "burger" which is the 4th word in the sentence.
//
// Constraints:
// 1 <= sentence.length <= 100
// 	1 <= searchWord.length <= 10
// 	sentence consists of lowercase English letters and spaces.
// 	searchWord consists of lowercase English letters.
//

class Solution {
    public int isPrefixOfWord(String sentence, String searchWord) {
        String[] words = sentence.split(" ");
        for (int i = 0; i < words.length; i++) {
            if (words[i].startsWith(searchWord)) {
                return i + 1;
            }
        }
        return -1;          
    }
}
