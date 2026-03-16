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

class Solution {
    public String shortestSuperstring(String[] words) {
        int n = words.length;
        int[][] overlap = new int[n][n];

        // Precompute the overlap between each pair of words
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    int maxOverlap = Math.min(words[i].length(), words[j].length());
                    for (int k = maxOverlap; k >= 0; k--) {
                        if (words[i].endsWith(words[j].substring(0, k))) {
                            overlap[i][j] = k;
                            break;
                        }
                    }
                }
            }
        }

        // DP to find the shortest superstring
        int[][] dp = new int[1 << n][n];
        int[][] parent = new int[1 << n][n];

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int bit = 0; bit < n; bit++) {
                if ((mask & (1 << bit)) == 0) continue;
                int prevMask = mask ^ (1 << bit);
                if (prevMask == 0) continue;

                for (int i = 0; i < n; i++) {
                    if ((prevMask & (1 << i)) == 0) continue;
                    int val = dp[prevMask][i] + words[bit].length() - overlap[i][bit];
                    if (val > dp[mask][bit]) {
                        dp[mask][bit] = val;
                        parent[mask][bit] = i;
                    }
                }
            }
        }

        // Reconstruct the shortest superstring
        int maxLen = -1;
        int last = -1;
        int finalMask = (1 << n) - 1;

        for (int i = 0; i < n; i++) {
            if (dp[finalMask][i] > maxLen) {
                maxLen = dp[finalMask][i];
                last = i;
            }
        }

        StringBuilder sb = new StringBuilder();
        boolean[] seen = new boolean[n];
        int mask = finalMask;

        while (mask > 0) {
            int prev = parent[mask][last];
            if (prev == 0 && (mask ^ (1 << last)) == 0) {
                sb.insert(0, words[last]);
            } else {
                sb.insert(0, words[last].substring(overlap[prev][last]));
            }
            seen[last] = true;
            mask ^= (1 << last);
            last = prev;
        }
        return sb.toString();
    }
}
