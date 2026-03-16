// Source: https://leetcode.com/problems/find-all-anagrams-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.
//
// Example:
// Input: s = "cbaebabacd", p = "abc"
// Output: [0,6]
// Explanation:
// The substring with start index = 0 is "cba", which is an anagram of "abc".
// The substring with start index = 6 is "bac", which is an anagram of "abc".
//
// Constraints:
// 1 <= s.length, p.length <= 3 * 104
// 	s and p consist of lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize) {
    int lenS = strlen(s);
    int lenP = strlen(p);
    int* result = (int*)malloc(lenS * sizeof(int));
    *returnSize = 0;

    if (lenS < lenP) {
        return result;
    }

    int countP[26] = {0};
    int countS[26] = {0};

    for (int i = 0; i < lenP; i++) {
        countP[p[i] - 'a']++;
        countS[s[i] - 'a']++;
    }

    for (int i = 0; i <= lenS - lenP; i++) {
        if (i > 0) {
            countS[s[i - 1] - 'a']--;
            countS[s[i + lenP - 1] - 'a']++;
        }

        if (memcmp(countP, countS, sizeof(countP)) == 0) {
            result[(*returnSize)++] = i;
        }
    }

    return result;      
}
