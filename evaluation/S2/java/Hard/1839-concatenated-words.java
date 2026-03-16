// Source: https://leetcode.com/problems/concatenated-words/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
//
// A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
//
// Example:
// Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
// Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
// Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
// "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
// "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
//
// Constraints:
// 1 <= words.length <= 104
// 	1 <= words[i].length <= 30
// 	words[i] consists of only lowercase English letters.
// 	All the strings of words are unique.
// 	1 <= sum(words[i].length) <= 105
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Aho-Corasick algorithm (trie, graph, bfs, trie-match)
//   • When to use: Use this algorithm to efficiently find all occurrences of a fixed set of patterns within a larger text. It is ideal for scenarios requiring simultaneous searching for multiple dictionary words.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns, allowing linear time searching for all pattern occurrences in a text. It extends a trie with suffix links and failure transitions for efficient traversal, achieving O(N + M + K) complexity where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All nodes at depth 'd' have their suffix links correctly computed before processing nodes at depth 'd+1'.; For any node 'u', its suffix link points to the longest proper suffix of the string represented by 'u' that is also a prefix of some pattern.
//   • Tips: Build the trie from all patterns first, marking nodes that represent the end of a pattern.; Compute suffix links using a breadth-first search (BFS) starting from the root.
//   • Pitfalls: Incorrectly computing suffix links can lead to wrong matches or infinite loops.; High memory usage can occur for large alphabets or a vast number of patterns.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<String> findAllConcatenatedWordsInADict(String[] words) {
        Set<String> wordSet = new HashSet<>(Arrays.asList(words));
        List<String> result = new ArrayList<>();

        for (String word : words) {
            if (canForm(word, wordSet)) {
                result.add(word);
            }
        }

        return result;          
    }
}
