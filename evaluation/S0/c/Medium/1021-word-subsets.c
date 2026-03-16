// Source: https://leetcode.com/problems/word-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given two string arrays words1 and words2.
//
// A string b is a subset of string a if every letter in b occurs in a including multiplicity.
//
//
// 	For example, "wrr" is a subset of "warrior" but is not a subset of "world".
//
//
// A string a from words1 is universal if for every string b in words2, b is a subset of a.
//
// Return an array of all the universal strings in words1. You may return the answer in any order.
//
// Example:
// Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
//
// Output: ["facebook","google","leetcode"]
//
// Constraints:
// 1 <= words1.length, words2.length <= 104
// 	1 <= words1[i].length, words2[i].length <= 10
// 	words1[i] and words2[i] consist only of lowercase English letters.
// 	All the strings of words1 are unique.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** wordSubsets(char** words1, int words1Size, char** words2, int words2Size, int* returnSize) {
    int maxFreq[26] = {0};
    for (int i = 0; i < words2Size; i++) {
        int freq[26] = {0};
        for (char* p = words2[i]; *p; p++) {
            freq[*p - 'a']++;
        }
        for (int j = 0; j < 26; j++) {
            if (freq[j] > maxFreq[j]) {
                maxFreq[j] = freq[j];
            }
        }
    }

    char** result = (char**)malloc(words1Size * sizeof(char*));
    *returnSize = 0;

    for (int i = 0; i < words1Size; i++) {
        int freq[26] = {0};
        for (char* p = words1[i]; *p; p++) {
            freq[*p - 'a']++;
        }

        int isUniversal = 1;
        for (int j = 0; j < 26; j++) {
            if (freq[j] < maxFreq[j]) {
                isUniversal = 0;
                break;
            }
        }

        if (isUniversal) {
            result[(*returnSize)++] = words1[i];
        }
    }

    return result;      
}
