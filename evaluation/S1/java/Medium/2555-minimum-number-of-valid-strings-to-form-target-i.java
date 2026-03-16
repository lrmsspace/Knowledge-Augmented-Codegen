// Source: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings words and a string target.
//
// A string x is called valid if x is a prefix of any string in words.
//
// Return the minimum number of valid strings that can be concatenated to form target. If it is not possible to form target, return -1.
//
// Example:
// Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"
//
// Output: 3
//
// Explanation:
//
// The target string can be formed by concatenating:
//
//
// 	Prefix of length 2 of words[1], i.e. "aa".
// 	Prefix of length 3 of words[2], i.e. "bcd".
// 	Prefix of length 3 of words[0], i.e. "abc".
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 5 * 103
// 	The input is generated such that sum(words[i].length) <= 105.
// 	words[i] consists only of lowercase English letters.
// 	1 <= target.length <= 5 * 103
// 	target consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Longest Increasing Subsequence (array, dp-1d)
//   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
//   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
//   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
//   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minValidStrings(String[] words, String target) {
        TrieNode root = buildTrie(words);
        int n = target.length();
        int[] dp = new int[n + 1];
        final int INF = Integer.MAX_VALUE / 2;
        for (int i = 1; i <= n; i++) {
            dp[i] = INF;
        }
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            TrieNode node = root;
            for (int j = i; j < n; j++) {
                char c = target.charAt(j);
                if (node.children[c - 'a'] == null) {
                    break;
                }
                node = node.children[c - 'a'];
                dp[j + 1] = Math.min(dp[j + 1], dp[i] + 1);
            }
        }

        return dp[n] == INF ? -1 : dp[n];           
    }
}
