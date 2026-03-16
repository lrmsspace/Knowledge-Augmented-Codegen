// Source: https://leetcode.com/problems/keyboard-row/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
//
// Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
//
// In the American keyboard:
//
//
// 	the first row consists of the characters "qwertyuiop",
// 	the second row consists of the characters "asdfghjkl", and
// 	the third row consists of the characters "zxcvbnm".
//
// Example:
// Input: words = ["Hello","Alaska","Dad","Peace"]
//
// Output: ["Alaska","Dad"]
//
// Explanation:
//
// Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.
//
// Constraints:
// 1 <= words.length <= 20
// 	1 <= words[i].length <= 100
// 	words[i] consists of English letters (both lowercase and uppercase).
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findWords(char** words, int wordsSize, int* returnSize) {
    int rowMap[26] = {0};
    for (char c = 'q'; c <= 'p'; ++c) {
        rowMap[c - 'a'] = 1;
    }
    for (char c = 'a'; c <= 'l'; ++c) {
        rowMap[c - 'a'] = 2;
    }
    for (char c = 'z'; c <= 'm'; ++c) {
        rowMap[c - 'a'] = 3;
    }

    char** result = (char**)malloc(wordsSize * sizeof(char*));
    int count = 0;

    for (int i = 0; i < wordsSize; ++i) {
        char* word = words[i];
        int firstCharRow = rowMap[tolower(word[0]) - 'a'];
        int j;
        for (j = 1; word[j] != '\0'; ++j) {
            if (rowMap[tolower(word[j]) - 'a'] != firstCharRow) {
                break;
            }
        }
        if (word[j] == '\0') {
            result[count++] = word;
        }
    }

    *returnSize = count;
    return result;      
}
