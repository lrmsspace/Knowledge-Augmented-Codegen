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
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: Used to optimize certain 2D dynamic programming problems, typically interval DP, where the cost function satisfies the quadrangle inequality and the optimal split points exhibit monotonicity.
//   • Idea: Knuth's Optimization reduces the time complexity of certain 2D DP problems from O(N^3) to O(N^2) by restricting the search range for the optimal split point. This is applicable when the cost function satisfies the quadrangle inequality and the optimal split points are monotonic.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for dp[i][j].
//   • Tips: Verify the quadrangle inequality for the cost function C(a,c) + C(b,d) <= C(a,d) + C(b,c).; Ensure the optimal split points opt[i][j] are monotonic: opt[i][j-1] <= opt[i][j] <= opt[i+1][j].
//   • Pitfalls: Incorrectly assuming quadrangle inequality holds for the cost function.; Improper iteration order for DP states, which breaks the opt dependency.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long minimumCost(String source, String target, String[] original, String[] changed, int[] cost) {
        int n = source.length();
        long[][] dp = new long[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = Long.MAX_VALUE;
            }
        }

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                String subSource = source.substring(i, j + 1);
                String subTarget = target.substring(i, j + 1);
                if (subSource.equals(subTarget)) {
                    dp[i][j] = 0;
                    continue;
                }
                for (int k = i; k < j; k++) {
                    if (dp[i][k] != Long.MAX_VALUE && dp[k + 1][j] != Long.MAX_VALUE) {
                        dp[i][j] = Math.min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                    }
                }
                for (int idx = 0; idx < original.length; idx++) {
                    if (original[idx].equals(subSource) && changed[idx].equals(subTarget)) {
                        dp[i][j] = Math.min(dp[i][j], cost[idx]);
                    }
                }
            }
        }

        return dp[0][n - 1] == Long.MAX_VALUE ? -1 : dp[0][n - 1];          
    }
}
