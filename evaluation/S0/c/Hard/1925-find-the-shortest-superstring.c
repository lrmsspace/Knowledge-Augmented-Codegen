// Source: https://leetcode.com/problems/find-the-shortest-superstring/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of strings words, return the smallest string that contains each string in words as a substring. If there are multiple valid strings of the smallest length, return any of them.
//
// You may assume that no string in words is a substring of another string in words.
//
// Example:
// Input: words = ["alex","loves","leetcode"]
// Output: "alexlovesleetcode"
// Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
//
// Constraints:
// 1 <= words.length <= 12
// 	1 <= words[i].length <= 20
// 	words[i] consists of lowercase English letters.
// 	All the strings of words are unique.
//

char* shortestSuperstring(char** words, int wordsSize) {
    int n = wordsSize;
    int overlap[12][12];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) { overlap[i][j] = 0; continue; }
            int max_ov = 0;
            int len_i = strlen(words[i]);
            int len_j = strlen(words[j]);
            int limit = len_i < len_j ? len_i : len_j;
            for (int k = 1; k <= limit; ++k) {
                if (strncmp(words[i] + len_i - k, words[j], k) == 0) {
                    max_ov = k;
                }
            }
            overlap[i][j] = max_ov;
        }
    }

    int dp[1 << 12][12];
    int parent[1 << 12][12];
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = 0;
    }

    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u)) || dp[mask][u] == -1) continue;
            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v)) continue;
                int nextMask = mask | (1 << v);
                int val = dp[mask][u] + overlap[u][v];
                if (val > dp[nextMask][v]) {
                    dp[nextMask][v] = val;
                    parent[nextMask][v] = u;
                }
            }
        }
    }

    int maxLen = -1, last = -1;
    int finalMask = (1 << n) - 1;
    for (int i = 0; i < n; ++i) {
        if (dp[finalMask][i] > maxLen) {
            maxLen = dp[finalMask][i];
            last = i;
        }
    }

    int path[12];
    int t = n - 1;
    int mask = finalMask;       
}
