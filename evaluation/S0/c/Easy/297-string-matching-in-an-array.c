// Source: https://leetcode.com/problems/string-matching-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of string words, return all strings in words that are a substring of another word. You can return the answer in any order.
//
// Example:
// Input: words = ["mass","as","hero","superhero"]
// Output: ["as","hero"]
// Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
// ["hero","as"] is also a valid answer.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 30
// 	words[i] contains only lowercase English letters.
// 	All the strings of words are unique.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** stringMatching(char** words, int wordsSize, int* returnSize) {
    char** result = malloc(wordsSize * sizeof(char*));
    int count = 0;

    for (int i = 0; i < wordsSize; i++) {
        for (int j = 0; j < wordsSize; j++) {
            if (i != j && strstr(words[j], words[i]) != NULL) {
                result[count++] = words[i];
                break;
            }
        }
    }

    *returnSize = count;
    return result;      
}
