// Source: https://leetcode.com/problems/minimum-cost-good-caption/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string caption of length n. A good caption is a string where every character appears in groups of at least 3 consecutive occurrences.
//
// For example:
//
//
// 	"aaabbb" and "aaaaccc" are good captions.
// 	"aabbb" and "ccccd" are not good captions.
//
//
// You can perform the following operation any number of times:
//
// Choose an index i (where 0 <= i < n) and change the character at that index to either:
//
//
// 	The character immediately before it in the alphabet (if caption[i] != 'a').
// 	The character immediately after it in the alphabet (if caption[i] != 'z').
//
//
// Your task is to convert the given caption into a good caption using the minimum number of operations, and return it. If there are multiple possible good captions, return the lexicographically smallest one among them. If it is impossible to create a good caption, return an empty string "".
//
// Example:
// Input: caption = "cdcd"
//
// Output: "cccc"
//
// Explanation:
//
// It can be shown that the given caption cannot be transformed into a good caption with fewer than 2 operations. The possible good captions that can be created using exactly 2 operations are:
//
//
// 	"dddd": Change caption[0] and caption[2] to their next character 'd'.
// 	"cccc": Change caption[1] and caption[3] to their previous character 'c'.
//
//
// Since "cccc" is lexicographically smaller than "dddd", return "cccc".
//
// Constraints:
// 1 <= caption.length <= 5 * 104
// 	caption consists only of lowercase English letters.
//

char* minCostGoodCaption(char* caption) {
    int n = strlen(caption);
    int INF = 1e9;
    int dp[n + 1][26];
    int pre[n + 1][26];
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < 26; ++j)
            dp[i][j] = INF;
    dp[0][0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 26; ++j) {
            int cost = abs(caption[i] - ('a' + j));
            for (int len = 3; len <= n - i; ++len) {
                int newCost = dp[i][j] + cost * len;
                if (newCost < dp[i + len][j]) {
                    dp[i + len][j] = newCost;
                    pre[i + len][j] = i;
                }
            }
        }
    }

    int minCost = INF;
    int lastChar = -1;
    for (int j = 0; j < 26; ++j) {
        if (dp[n][j] < minCost) {
            minCost = dp[n][j];
            lastChar = j;
        }
    }
    if (minCost == INF) return "";

    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[n] = '\0';
    int idx = n;
    while (idx > 0) {
        int startIdx = pre[idx][lastChar];
        for (int k = startIdx; k < idx; ++k)
            result[k] = 'a' + lastChar;
        idx = startIdx;
    }

    return result;      
}
