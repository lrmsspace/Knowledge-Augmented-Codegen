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

class Solution {
    public String minCostGoodCaption(String caption) {
        int n = caption.length();
        int[][] dp = new int[n + 1][3];
        char[][] choice = new char[n + 1][3];
        final int INF = (int) 1e9;

        for (int i = n - 1; i >= 0; i--) {
            for (char c = 'a'; c <= 'z'; c++) {
                int cost = caption.charAt(i) == c ? 0 : 1;

                // Case 1: Start a new group of character c
                if (dp[i + 1][0] + cost < dp[i][0]) {
                    dp[i][0] = dp[i + 1][0] + cost;
                    choice[i][0] = c;
                }

                // Case 2: Continue an existing group of character c
                for (int len = 1; len <= 2; len++) {
                    if (dp[i + 1][len] + cost < dp[i][len + 1]) {
                        dp[i][len + 1] = dp[i + 1][len] + cost;
                        choice[i][len + 1] = c;
                    }
                }
            }
        }

        if (dp[0][0] >= INF) {
            return "";
        }

        StringBuilder result = new StringBuilder();
        int len = 0;
        for (int i = 0; i < n; i++) {
            char c = choice[i][len];
            result.append(c);
            if (c == choice[i + 1][len]) {
                len++;
            } else {
                len = 0;
            }
        }

        return result.toString();           
    }
}
