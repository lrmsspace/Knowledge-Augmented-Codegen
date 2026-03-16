// Source: https://leetcode.com/problems/edit-distance/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
//
// You have the following three operations permitted on a word:
//
//
// 	Insert a character
// 	Delete a character
// 	Replace a character
//
// Example:
// Input: word1 = "horse", word2 = "ros"
// Output: 3
// Explanation: 
// horse -> rorse (replace 'h' with 'r')
// rorse -> rose (remove 'r')
// rose -> ros (remove 'e')
//
// Constraints:
// 0 <= word1.length, word2.length <= 500
// 	word1 and word2 consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
//   • When to use: Use when needing to find the shortest paths between all pairs of vertices in a weighted graph, especially if negative edge weights are present but no negative cycles.
//   • Idea: The Floyd-Warshall algorithm is a dynamic programming approach that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path lengths, achieving an O(N^3) time complexity.
//   • Invariants: After k iterations, d[i][j] stores the shortest path from i to j using only vertices {1, ..., k} as intermediate nodes.; d[i][j] always represents a valid path length or infinity, never an invalid negative value unless a negative cycle is detected.
//   • Tips: Initialize direct edge weights and infinity for non-existent edges.; Set distance from a vertex to itself to zero initially.
//   • Pitfalls: Incorrect loop order (k must be outermost) will yield incorrect results.; Improper handling of 'infinity' values can lead to overflow or incorrect comparisons.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - Floyd-Warshall Algorithm (matrix, graph, recursion, dp-2d)
//   • When to use: Use when you need to find the shortest paths between all pairs of vertices in a weighted graph. It is suitable for graphs with negative edge weights but no negative cycles.
//   • Idea: The Floyd-Warshall algorithm finds all-pairs shortest paths in a weighted graph using dynamic programming. It iteratively considers all possible intermediate vertices, updating path lengths in O(V^3) time.
//   • Invariants: After k iterations, dist[i][j] contains the shortest path from i to j using only vertices 0 to k-1 as intermediate nodes.; dist[i][j] is always non-increasing with each iteration of k.
//   • Tips: Initialize distances with edge weights or infinity, and 0 for self-loops.; The outermost loop iterates through intermediate vertices (k).
//   • Pitfalls: Incorrectly handling infinity values, especially with negative weights (e.g., infinity - 1).; Not checking for negative cycles, which can lead to incorrect shortest path values.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (i == 0) {
                    dp[i][j] = j; // If word1 is empty, insert all characters of word2
                } else if (j == 0) {
                    dp[i][j] = i; // If word2 is empty, remove all characters of word1
                } else if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1]; // No operation needed
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j],    // Remove character from word1
                                         dp[i][j - 1],    // Insert character into word1
                                         dp[i - 1][j - 1] // Replace character in word1
                                        });
                }
            }
        }

        return dp[m][n];            
    }
};
