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
// Helpful references (internal KB):
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Suffix Array (string, array, merge-sort)
//   • When to use: Use when needing to efficiently query properties of all suffixes or substrings of a given text, especially for pattern matching or finding repeated structures. It is particularly useful for problems requiring lexicographical ordering of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices. It enables efficient string operations like pattern searching and finding longest common prefixes, typically constructed in O(N log N) time.
//   • Invariants: After k iterations, suffixes are sorted correctly up to a certain length (e.g., 2^k).; All suffixes of the original string are represented by their starting indices in the array.
//   • Tips: Append a unique sentinel character (e.g., '$') smaller than any other character to the string.; Utilize the LCP array, often built alongside, for advanced string queries and optimizations.
//   • Pitfalls: Naive sorting of suffixes by string comparison leads to an inefficient O(N^2 log N) complexity.; High memory usage for very long strings due to storing all suffixes implicitly or explicitly.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String shortestSuperstring(String[] words) {
        int n = words.length;
        int[][] overlap = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    overlap[i][j] = getOverlap(words[i], words[j]);
                }
            }
        }

        int[][] dp = new int[1 << n][n];
        int[][] parent = new int[1 << n][n];
        for (int mask = 0; mask < (1 << n); mask++) {
            Arrays.fill(dp[mask], Integer.MAX_VALUE / 2);
            Arrays.fill(parent[mask], -1);
        }

        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = words[i].length();
        }

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int last = 0; last < n; last++) {
                if ((mask & (1 << last)) == 0) continue;
                int prevMask = mask ^ (1 << last);
                if (prevMask == 0) continue;

                for (int prevLast = 0; prevLast < n; prevLast++) {
                    if ((prevMask & (1 << prevLast)) == 0) continue;
                    int cost = dp[prevMask][prevLast] + overlap[prevLast][last];
                    if (cost < dp[mask][last]) {
                        dp[mask][last] = cost;
                        parent[mask][last] = prevLast;
                    }
                }
            }
        }

        int minLen = Integer.MAX_VALUE;
        int lastIndex = -1;
        for (int i = 0; i < n; i++) {
            if (dp[(1 << n) - 1][i] < minLen) {
                minLen = dp[(1 << n) - 1][i];
                lastIndex = i;
            }
        }

        StringBuilder sb = new StringBuilder();
        int mask = (1 << n) - 1;
        while (lastIndex != -1) {
            sb.insert(0, words[lastIndex]);
            int prevIndex = parent[mask][lastIndex];
            if (prevIndex != -1) {       
                sb.delete(0, overlap[prevIndex][lastIndex]);
            }
            mask ^= (1 << lastIndex);
            lastIndex = prevIndex;
        }
        return sb.toString();   
    }
}
