// Source: https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called almost equal to y if you can change at most one character in x to make it identical to y.
//
// A sequence of indices seq is called valid if:
//
//
// 	The indices are sorted in ascending order.
// 	Concatenating the characters at these indices in word1 in the same order results in a string that is almost equal to word2.
//
//
// Return an array of size word2.length representing the lexicographically smallest valid sequence of indices. If no such sequence of indices exists, return an empty array.
//
// Note that the answer must represent the lexicographically smallest array, not the corresponding string formed by those indices.
//
// Example:
// Input: word1 = "vbcca", word2 = "abc"
//
// Output: [0,1,2]
//
// Explanation:
//
// The lexicographically smallest valid sequence of indices is [0, 1, 2]:
//
//
// 	Change word1[0] to 'a'.
// 	word1[1] is already 'b'.
// 	word1[2] is already 'c'.
//
// Constraints:
// 1 <= word2.length < word1.length <= 3 * 105
// 	word1 and word2 consist only of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* validSequence(char* word1, char* word2, int* returnSize) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int *res = (int *)malloc(sizeof(int) * len2);
    int resIdx = 0;
    int diffCount = 0;
    int i, j;

    for (i = 0, j = 0; i < len1 && j < len2; i++) {
        if (word1[i] == word2[j]) {
            res[resIdx++] = i;
            j++;
        } else {
            diffCount++;
            if (diffCount > 1) {
                // More than one character difference, return empty array
                free(res);
                *returnSize = 0;
                return NULL;
            }
        }
    }

    // If we have not matched all characters in word2
    if (j < len2) {
        diffCount += (len2 - j);
    }

    if (diffCount > 1) {
        // More than one character difference, return empty array
        free(res);
        *returnSize = 0;
        return NULL;
    }

    *returnSize = resIdx;
    return res;     
}
