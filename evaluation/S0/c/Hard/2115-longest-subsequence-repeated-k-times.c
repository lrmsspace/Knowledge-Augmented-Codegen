// Source: https://leetcode.com/problems/longest-subsequence-repeated-k-times/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s of length n, and an integer k. You are tasked to find the longest subsequence repeated k times in string s.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// A subsequence seq is repeated k times in the string s if seq * k is a subsequence of s, where seq * k represents a string constructed by concatenating seq k times.
//
//
// 	For example, "bba" is repeated 2 times in the string "bababcba", because the string "bbabba", constructed by concatenating "bba" 2 times, is a subsequence of the string "bababcba".
//
//
// Return the longest subsequence repeated k times in string s. If multiple such subsequences are found, return the lexicographically largest one. If there is no such subsequence, return an empty string.
//
// Example:
// Input: s = "letsleetcode", k = 2
// Output: "let"
// Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
// "let" is the lexicographically largest one.
//
// Constraints:
// n == s.length
// 	2 <= k <= 2000
// 	2 <= n < min(2001, k * 8)
// 	s consists of lowercase English letters.
//

char* longestSubsequenceRepeatedK(char* s, int k) {
    int len = strlen(s);
    int count[26];
    for (int i = 0; i < 26; i++) count[i] = 0;
    for (int i = 0; i < len; i++) count[s[i] - 'a']++;
    char candidates[26];
    int candSize = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] >= k) {
            candidates[candSize++] = (char)(i + 'a');
            count[i] /= k;
        }
    }
    char *best = (char*)malloc(1);
    best[0] = '\0';
    int bestLen = 0;

    int totalComb = 1 << candSize;
    for (int comb = 1; comb < totalComb; comb++) {
        char path[21];
        int pathLen = 0;
        for (int i = 0; i < candSize; i++) {
            if (comb & (1 << i)) {
                for (int c = 0; c < count[candidates[i] - 'a']; c++) {
                    path[pathLen++] = candidates[i];
                }
            }
        }
        path[pathLen] = '\0';
        qsort(path, pathLen, sizeof(char), cmpInt);

        // Check if path * k is subsequence of s
        int si = 0, pi = 0, repeat = 0;
        while (si < len && repeat < k) {
            if (s[si] == path[pi]) {
                pi++;
                if (pi == pathLen) {
                    pi = 0;
                    repeat++;
                }
            }
            si++;
        }
        if (repeat == k) {
            if (pathLen > bestLen || (pathLen == bestLen && strcmp(path, best) > 0)) {
                free(best);
                best = (char*)malloc(pathLen + 1);
                strcpy(best, path);
                bestLen = pathLen;
            }
        }
    }
    return best;        
}
