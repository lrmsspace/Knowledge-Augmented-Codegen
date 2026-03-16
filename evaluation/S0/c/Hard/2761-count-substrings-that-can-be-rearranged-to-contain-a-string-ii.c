// Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called valid if x can be rearranged to have word2 as a prefix.
//
// Return the total number of valid substrings of word1.
//
// Note that the memory limits in this problem are smaller than usual, so you must implement a solution with a linear runtime complexity.
//
// Example:
// Input: word1 = "bcca", word2 = "abc"
//
// Output: 1
//
// Explanation:
//
// The only valid substring is "bcca" which can be rearranged to "abcc" having "abc" as a prefix.
//
// Constraints:
// 1 <= word1.length <= 106
// 	1 <= word2.length <= 104
// 	word1 and word2 consist only of lowercase English letters.
//

long long validSubstringCount(char* word1, char* word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    if (len1 < len2) return 0;

    int need[26] = {0};
    for (int i = 0; i < len2; i++) {
        need[word2[i] - 'a']++;
    }

    int have[26] = {0};
    long long result = 0;
    int left = 0, right = 0;
    int required = 0; // number of characters still needed

    for (int i = 0; i < 26; i++) {
        if (need[i] > 0) {
            required++;
        }
    }

    while (right < len1) {
        int idxR = word1[right] - 'a';
        if (need[idxR] > 0) {
            have[idxR]++;
            if (have[idxR] == need[idxR]) {
                required--;
            }
        }
        right++;

        while (required == 0) {
            result += (len1 - right + 1); // all substrings starting from left to end are valid
            int idxL = word1[left] - 'a';
            if (need[idxL] > 0) {
                have[idxL]--;
                if (have[idxL] < need[idxL]) {
                    required++;
                }
            }
            left++;
        }
    }

    return result;      
}
