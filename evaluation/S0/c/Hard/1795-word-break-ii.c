// Source: https://leetcode.com/problems/word-break-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.
//
// Note that the same word in the dictionary may be reused multiple times in the segmentation.
//
// Example:
// Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
// Output: ["cats and dog","cat sand dog"]
//
// Constraints:
// 1 <= s.length <= 20
// 	1 <= wordDict.length <= 1000
// 	1 <= wordDict[i].length <= 10
// 	s and wordDict[i] consist of only lowercase English letters.
// 	All the strings of wordDict are unique.
// 	Input is generated in a way that the length of the answer doesn't exceed 105.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** wordBreak(char* s, char** wordDict, int wordDictSize, int* returnSize) {

    *returnSize = 0;
    int sLen = strlen(s);
    
    // DP to check if s can be segmented
    int* dp = (int*)calloc(sLen + 1, sizeof(int));
    dp[0] = 1;
    
    for (int i = 1; i <= sLen; i++) {
        for (int j = 0; j < wordDictSize; j++) {
            int wLen = strlen(wordDict[j]);
            if (i >= wLen && dp[i - wLen] && strncmp(&s[i - wLen], wordDict[j], wLen) == 0) {
                dp[i] = 1;
                break;
            }
        }
    }
    
    if (!dp[sLen]) {
        free(dp);
        return NULL;
    }
    
    free(dp);
    
    // Backtracking to find all sentences
    char** results = NULL;
    int resultsCap = 0;
    
    void backtrack(int start, char* path, int pathLen) {
        if (start == sLen) {
            if (*returnSize >= resultsCap) {
                resultsCap = resultsCap == 0 ? 16 : resultsCap * 2;
                results = (char**)realloc(results, resultsCap * sizeof(char*));
            }
            path[pathLen - 1] = '\0'; // Replace last space with null terminator
            results[*returnSize] = strdup(path);
            (*returnSize)++;
            return;
        }
        
        for (int i = start + 1; i <= sLen; i++) {
            for (int j = 0; j < wordDictSize; j++) {
                int wLen = strlen(wordDict[j]);
                if (i - start == wLen && strncmp(&s[start], wordDict[j], wLen) == 0) {
                    memcpy(&path[pathLen], wordDict[j], wLen);
                    path[pathLen + wLen] = ' ';
                    backtrack(i, path, pathLen + wLen + 1);
                }
            }
        }
    }
    
    char* path = (char*)malloc((sLen + wordDictSize) * sizeof(char)); // Extra space for spaces
    backtrack(0, path, 0);
    free(path);
    
    return results;
            
}
