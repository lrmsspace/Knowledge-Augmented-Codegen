// Source: https://leetcode.com/problems/find-and-replace-pattern/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of strings words and a string pattern, return a list of words[i] that match pattern. You may return the answer in any order.
//
// A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.
//
// Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.
//
// Example:
// Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
// Output: ["mee","aqq"]
// Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
// "ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation, since a and b map to the same letter.
//
// Constraints:
// 1 <= pattern.length <= 20
// 	1 <= words.length <= 50
// 	words[i].length == pattern.length
// 	pattern and words[i] are lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findAndReplacePattern(char** words, int wordsSize, char* pattern, int* returnSize) {
    char** result = (char**)malloc(wordsSize * sizeof(char*));
    int count = 0;
    int patternLen = strlen(pattern);

    for (int i = 0; i < wordsSize; i++) {
        char* word = words[i];
        if (strlen(word) != patternLen) {
            continue;
        }

        char mapWtoP[26] = {0};
        char mapPtoW[26] = {0};
        int match = 1;

        for (int j = 0; j < patternLen; j++) {
            char wChar = word[j];
            char pChar = pattern[j];

            if (mapWtoP[wChar - 'a'] == 0 && mapPtoW[pChar - 'a'] == 0) {
                mapWtoP[wChar - 'a'] = pChar;
                mapPtoW[pChar - 'a'] = wChar;
            } else if (mapWtoP[wChar - 'a'] != pChar || mapPtoW[pChar - 'a'] != wChar) {
                match = 0;
                break;
            }
        }

        if (match) {
            result[count++] = word;
        }
    }

    *returnSize = count;
    return result;      
}
