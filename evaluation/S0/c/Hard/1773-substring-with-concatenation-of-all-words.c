// Source: https://leetcode.com/problems/substring-with-concatenation-of-all-words/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an array of strings words. All the strings of words are of the same length.
//
// A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.
//
//
// 	For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
//
//
// Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.
//
// Example:
// Input: s = "barfoothefoobarman", words = ["foo","bar"]
//
// Output: [0,9]
//
// Explanation:
//
// The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
// The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
//
// Constraints:
// 1 <= s.length <= 104
// 	1 <= words.length <= 5000
// 	1 <= words[i].length <= 30
// 	s and words[i] consist of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    int wordLen = strlen(words[0]);
    int substringLen = wordLen * wordsSize;
    int sLen = strlen(s);
    int* result = (int*)malloc(sizeof(int) * (sLen - substringLen + 1));
    *returnSize = 0;

    if (wordsSize == 0 || sLen < substringLen) {
        return result;
    }

    // Create a frequency map for the words
    #define ALPHABET_SIZE 26
    #define MAX_WORDS 5000
    #define MAX_WORD_LEN 30

    typedef struct {
        char word[MAX_WORD_LEN + 1];
        int count;
    } WordCount;

    WordCount wordCountMap[MAX_WORDS];
    int uniqueWords = 0;

    for (int i = 0; i < wordsSize; i++) {
        int found = 0;
        for (int j = 0; j < uniqueWords; j++) {
            if (strcmp(wordCountMap[j].word, words[i]) == 0) {
                wordCountMap[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(wordCountMap[uniqueWords].word, words[i]);
            wordCountMap[uniqueWords].count = 1;
            uniqueWords++;
        }
    }

    // Check each possible starting index in s
    for (int i = 0; i <= sLen - substringLen; i++) {
        int tempCount[MAX_WORDS] = {0};
        int j;
        for (j = 0; j < wordsSize; j++) {
            char subWord[MAX_WORD_LEN + 1];
            strncpy(subWord, s + i + j * wordLen, wordLen);
            subWord[wordLen] = '\0';

            int found = 0;
            for (int k = 0; k < uniqueWords; k++) {
                if (strcmp(wordCountMap[k].word, subWord) == 0) {
                    tempCount[k]++;
                    if (tempCount[k] > wordCountMap[k].count) {
                        break;
                    }
                    found = 1;
                    break;
                }
            }
            if (!found || (j < wordsSize && tempCount[k] > wordCountMap[k].count)) {
                break;
            }
        }
        if (j == wordsSize) {
            result[*returnSize] = i;
            (*returnSize)++;
        }
        
    }

    return result;
}
