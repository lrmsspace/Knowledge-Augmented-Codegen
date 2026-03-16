// Source: https://leetcode.com/problems/check-if-dfs-strings-are-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// You are given a tree rooted at node 0, consisting of n nodes numbered from 0 to n - 1. The tree is represented by an array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
//
// You are also given a string s of length n, where s[i] is the character assigned to node i.
//
// Consider an empty string dfsStr, and define a recursive function dfs(int x) that takes a node x as a parameter and performs the following steps in order:
//
//
// 	Iterate over each child y of x in increasing order of their numbers, and call dfs(y).
// 	Add the character s[x] to the end of the string dfsStr.
//
//
// Note that dfsStr is shared across all recursive calls of dfs.
//
// You need to find a boolean array answer of size n, where for each index i from 0 to n - 1, you do the following:
//
//
// 	Empty the string dfsStr and call dfs(i).
// 	If the resulting string dfsStr is a palindrome, then set answer[i] to true. Otherwise, set answer[i] to false.
//
//
// Return the array answer.
//
// Example:
// Input: parent = [-1,0,0,1,1,2], s = "aababa"
//
// Output: [true,true,false,true,true,true]
//
// Explanation:
//
//
// 	Calling dfs(0) results in the string dfsStr = "abaaba", which is a palindrome.
// 	Calling dfs(1) results in the string dfsStr = "aba", which is a palindrome.
// 	Calling dfs(2) results in the string dfsStr = "ab", which is not a palindrome.
// 	Calling dfs(3) results in the string dfsStr = "a", which is a palindrome.
// 	Calling dfs(4) results in the string dfsStr = "b", which is a palindrome.
// 	Calling dfs(5) results in the string dfsStr = "a", which is a palindrome.
//
// Constraints:
// n == parent.length == s.length
// 	1 <= n <= 105
// 	0 <= parent[i] <= n - 1 for all i >= 1.
// 	parent[0] == -1
// 	parent represents a valid tree.
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
//   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
//   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
//   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
//   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean[] findAnswer(int[] parent, String s) {
        int n = parent.length;
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tree.add(new ArrayList<>());
        }
        for (int i = 1; i < n; i++) {
            tree.get(parent[i]).add(i);
        }

        boolean[] answer = new boolean[n];
        StringBuilder dfsStr = new StringBuilder();

        for (int i = 0; i < n; i++) {
            dfsStr.setLength(0);
            dfs(tree, s, dfsStr, i);
            answer[i] = isPalindrome(dfsStr);
        }

        return answer;          
    }
}
