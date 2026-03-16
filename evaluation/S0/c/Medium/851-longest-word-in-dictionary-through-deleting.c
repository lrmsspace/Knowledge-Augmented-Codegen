// Source: https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
//
// Example:
// Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
// Output: "apple"
//
// Constraints:
// 1 <= s.length <= 1000
// 	1 <= dictionary.length <= 1000
// 	1 <= dictionary[i].length <= 1000
// 	s and dictionary[i] consist of lowercase English letters.
//

char* findLongestWord(char* s, char** dictionary, int dictionarySize) {
    char* res = "";
    for (int i = 0; i < dictionarySize; i++) {
        char* word = dictionary[i];
        int m = strlen(s), n = strlen(word);
        int j = 0;
        for (int k = 0; k < m && j < n; k++) {
            if (s[k] == word[j]) {
                j++;
            }
        }
        if (j == n) {
            if (n > strlen(res) || (n == strlen(res) && strcmp(word, res) < 0)) {
                res = word;
            }
        }
    }
    return res;     
}
