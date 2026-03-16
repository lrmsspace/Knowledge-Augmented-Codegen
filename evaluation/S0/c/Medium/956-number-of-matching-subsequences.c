// Source: https://leetcode.com/problems/number-of-matching-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s.
//
// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
//
// 	For example, "ace" is a subsequence of "abcde".
//
// Example:
// Input: s = "abcde", words = ["a","bb","acd","ace"]
// Output: 3
// Explanation: There are three strings in words that are a subsequence of s: "a", "acd", "ace".
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	1 <= words.length <= 5000
// 	1 <= words[i].length <= 50
// 	s and words[i] consist of only lowercase English letters.
//

int numMatchingSubseq(char* s, char** words, int wordsSize) {
    int count = 0;
    int len_s = strlen(s);

    for (int i = 0; i < wordsSize; i++) {
        char* word = words[i];
        int len_word = strlen(word);
        int index_s = 0, index_word = 0;

        while (index_s < len_s && index_word < len_word) {
            if (s[index_s] == word[index_word]) {
                index_word++;
            }
            index_s++;
        }

        if (index_word == len_word) {
            count++;
        }
    }

    return count;       
}
