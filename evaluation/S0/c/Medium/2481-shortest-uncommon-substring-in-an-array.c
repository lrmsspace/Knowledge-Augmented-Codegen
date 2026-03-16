// Source: https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array arr of size n consisting of non-empty strings.
//
// Find a string array answer of size n such that:
//
//
// 	answer[i] is the shortest substring of arr[i] that does not occur as a substring in any other string in arr. If multiple such substrings exist, answer[i] should be the lexicographically smallest. And if no such substring exists, answer[i] should be an empty string.
//
//
// Return the array answer.
//
// Example:
// Input: arr = ["cab","ad","bad","c"]
// Output: ["ab","","ba",""]
// Explanation: We have the following:
// - For the string "cab", the shortest substring that does not occur in any other string is either "ca" or "ab", we choose the lexicographically smaller substring, which is "ab".
// - For the string "ad", there is no substring that does not occur in any other string.
// - For the string "bad", the shortest substring that does not occur in any other string is "ba".
// - For the string "c", there is no substring that does not occur in any other string.
//
// Constraints:
// n == arr.length
// 	2 <= n <= 100
// 	1 <= arr[i].length <= 20
// 	arr[i] consists only of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** shortestSubstrings(char** arr, int arrSize, int* returnSize) {
    *returnSize = arrSize;
    char** result = (char**)malloc(arrSize * sizeof(char*));
    for (int i = 0; i < arrSize; i++) {
        result[i] = NULL;
        int len = strlen(arr[i]);
        int found = 0;
        for (int subLen = 1; subLen <= len && !found; subLen++) {
            for (int start = 0; start <= len - subLen && !found; start++) {
                char substring[21];
                strncpy(substring, arr[i] + start, subLen);
                substring[subLen] = '\0';
                
                int isUnique = 1;
                for (int j = 0; j < arrSize; j++) {
                    if (j != i && strstr(arr[j], substring) != NULL) {
                        isUnique = 0;
                        break;
                    }
                }
                
                if (isUnique) {
                    if (result[i] == NULL || strcmp(substring, result[i]) < 0) {
                        if (result[i] != NULL) {
                            free(result[i]);
                        }
                        result[i] = strdup(substring);
                    }
                    found = 1;
                }
            }
        }
        if (result[i] == NULL) {
            result[i] = strdup("");
        }
    }
    return result;      
}
