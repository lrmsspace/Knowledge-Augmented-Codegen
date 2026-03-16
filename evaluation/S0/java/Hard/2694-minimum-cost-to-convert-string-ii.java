// Source: https://leetcode.com/problems/minimum-cost-to-convert-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English characters. You are also given two 0-indexed string arrays original and changed, and an integer array cost, where cost[i] represents the cost of converting the string original[i] to the string changed[i].
//
// You start with the string source. In one operation, you can pick a substring x from the string, and change it to y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y. You are allowed to do any number of operations, but any pair of operations must satisfy either of these two conditions:
//
//
// 	The substrings picked in the operations are source[a..b] and source[c..d] with either b < c or d < a. In other words, the indices picked in both operations are disjoint.
// 	The substrings picked in the operations are source[a..b] and source[c..d] with a == c and b == d. In other words, the indices picked in both operations are identical.
//
//
// Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.
//
// Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
//
// Example:
// Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
// Output: 28
// Explanation: To convert "abcd" to "acbe", do the following operations:
// - Change substring source[1..1] from "b" to "c" at a cost of 5.
// - Change substring source[2..2] from "c" to "e" at a cost of 1.
// - Change substring source[2..2] from "e" to "b" at a cost of 2.
// - Change substring source[3..3] from "d" to "e" at a cost of 20.
// The total cost incurred is 5 + 1 + 2 + 20 = 28. 
// It can be shown that this is the minimum possible cost.
//
// Constraints:
// 1 <= source.length == target.length <= 1000
// 	source, target consist only of lowercase English characters.
// 	1 <= cost.length == original.length == changed.length <= 100
// 	1 <= original[i].length == changed[i].length <= source.length
// 	original[i], changed[i] consist only of lowercase English characters.
// 	original[i] != changed[i]
// 	1 <= cost[i] <= 106
//

class Solution {
    public long minimumCost(String source, String target, String[] original, String[] changed, int[] cost) {
        int n = source.length();
        long[][] dp = new long[n + 1][n + 1];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = Long.MAX_VALUE;
            }
        }
        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] == Long.MAX_VALUE) continue;

                if (source.charAt(i) == target.charAt(j)) {
                    dp[i + 1][j + 1] = Math.min(dp[i + 1][j + 1], dp[i][j]);
                }

                for (int k = 0; k < original.length; k++) {
                    String o = original[k];
                    String c = changed[k];
                    int len = o.length();

                    if (i + len <= n && j + len <= n &&
                        source.substring(i, i + len).equals(o) &&
                        target.substring(j, j + len).equals(c)) {
                        dp[i + len][j + len] = Math.min(dp[i + len][j + len], dp[i][j] + cost[k]);
                    }
                }
            }
        }

        return dp[n][n] == Long.MAX_VALUE ? -1 : dp[n][n];          
    }
}
