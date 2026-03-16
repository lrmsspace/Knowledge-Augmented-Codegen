// Source: https://leetcode.com/problems/subsequence-with-the-minimum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and t.
//
// You are allowed to remove any number of characters from the string t.
//
// The score of the string is 0 if no characters are removed from the string t, otherwise:
//
//
// 	Let left be the minimum index among all removed characters.
// 	Let right be the maximum index among all removed characters.
//
//
// Then the score of the string is right - left + 1.
//
// Return the minimum possible score to make t a subsequence of s.
//
// A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
//
// Example:
// Input: s = "abacaba", t = "bzaa"
// Output: 1
// Explanation: In this example, we remove the character "z" at index 1 (0-indexed).
// The string t becomes "baa" which is a subsequence of the string "abacaba" and the score is 1 - 1 + 1 = 1.
// It can be proven that 1 is the minimum score that we can achieve.
//
// Constraints:
// 1 <= s.length, t.length <= 105
// 	s and t consist of only lowercase English letters.
//

int minimumScore(char* s, char* t) {
    int sLen = strlen(s);
    int tLen = strlen(t);
    int *leftPos = (int*)malloc((tLen + 1) * sizeof(int));
    int *rightPos = (int*)malloc((tLen + 1) * sizeof(int));
    if (!leftPos || !rightPos) {
        free(leftPos); free(rightPos); return -1; /* allocation failure */
    }

    /* Compute leftPos */
    int si = 0, ti = 0;
    while (si < sLen && ti < tLen) {
        if (s[si] == t[ti]) {
            leftPos[ti] = si;
            ti++;
        }
        si++;
    }
    if (ti < tLen) {
        /* t is not a subsequence of s */
        free(leftPos); free(rightPos); return tLen;
    }
    leftPos[tLen] = sLen; /* sentinel */

    /* Compute rightPos */
    si = sLen - 1; ti = tLen - 1;
    while (si >= 0 && ti >= 0) {
        if (s[si] == t[ti]) {
            rightPos[ti] = si;
            ti--;
        }
        si--;
    }
    rightPos[-1 + 1] = -1; /* sentinel */

    /* Find minimum score */
    int minScore = tLen; /* worst case: remove all characters from t */
    for (int i = -1; i < tLen; ++i) {
        int leftIndex = leftPos[i + 1];
        int rightIndex = rightPos[i + 1];
        if (rightIndex == -1 || leftIndex == sLen) continue;
        int score = rightIndex - leftIndex + 1;
        if (score < minScore) minScore = score;
    }

    free(leftPos);
    free(rightPos);
    return minScore;        
}
