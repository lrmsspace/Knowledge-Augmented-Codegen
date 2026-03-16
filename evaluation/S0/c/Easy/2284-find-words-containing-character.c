// Source: https://leetcode.com/problems/find-words-containing-character/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of strings words and a character x.
//
// Return an array of indices representing the words that contain the character x.
//
// Note that the returned array may be in any order.
//
// Example:
// Input: words = ["leet","code"], x = "e"
// Output: [0,1]
// Explanation: "e" occurs in both words: "leet", and "code". Hence, we return indices 0 and 1.
//
// Constraints:
// 1 <= words.length <= 50
// 	1 <= words[i].length <= 50
// 	x is a lowercase English letter.
// 	words[i] consists only of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findWordsContaining(char** words, int wordsSize, char x, int* returnSize) {
    int* result = (int*)malloc(wordsSize * sizeof(int));
    int count = 0;

    for (int i = 0; i < wordsSize; i++) {
        char* word = words[i];
        for (int j = 0; word[j] != '\0'; j++) {
            if (word[j] == x) {
                result[count++] = i;
                break;
            }
        }
    }

    *returnSize = count;
    return result;      
}
