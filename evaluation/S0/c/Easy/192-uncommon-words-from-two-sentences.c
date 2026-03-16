// Source: https://leetcode.com/problems/uncommon-words-from-two-sentences/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a string of single-space separated words where each word consists only of lowercase letters.
//
// A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.
//
// Given two sentences s1 and s2, return a list of all the uncommon words. You may return the answer in any order.
//
// Example:
// Input: s1 = "this apple is sweet", s2 = "this apple is sour"
//
// Output: ["sweet","sour"]
//
// Explanation:
//
// The word "sweet" appears only in s1, while the word "sour" appears only in s2.
//
// Constraints:
// 1 <= s1.length, s2.length <= 200
// 	s1 and s2 consist of lowercase English letters and spaces.
// 	s1 and s2 do not have leading or trailing spaces.
// 	All the words in s1 and s2 are separated by a single space.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** uncommonFromSentences(char* s1, char* s2, int* returnSize) {
    #define MAX_WORDS 100
    #define MAX_WORD_LENGTH 21

    char* words[MAX_WORDS * 2];
    int counts[MAX_WORDS * 2] = {0};
    int wordCount = 0;

    // Helper function to add words to the list
    void addWord(char* word) {
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(words[i], word) == 0) {
                counts[i]++;
                return;
            }
        }
        words[wordCount] = strdup(word);
        counts[wordCount] = 1;
        wordCount++;
    }

    // Tokenize and count words in s1
    char* token = strtok(s1, " ");
    while (token != NULL) {
        addWord(token);
        token = strtok(NULL, " ");
    }

    // Tokenize and count words in s2
    token = strtok(s2, " ");
    while (token != NULL) {
        addWord(token);
        token = strtok(NULL, " ");
    }

    // Collect uncommon words
    char** result = malloc(MAX_WORDS * sizeof(char*));
    *returnSize = 0;
    for (int i = 0; i < wordCount; i++) {
        if (counts[i] == 1) {
            result[*returnSize] = words[i];
            (*returnSize)++;
        } else {
            free(words[i]); // Free unused words
        }
    }

    return result;      
}
