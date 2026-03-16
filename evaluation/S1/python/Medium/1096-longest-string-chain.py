# Source: https://leetcode.com/problems/longest-string-chain/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of words where each word consists of lowercase English letters.
#
# wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.
#
#
# 	For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
#
#
# A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.
#
# Return the length of the longest possible word chain with words chosen from the given list of words.
#
# Example:
# Input: words = ["a","b","ba","bca","bda","bdca"]
# Output: 4
# Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
#
# Constraints:
# 1 <= words.length <= 1000
# 	1 <= words[i].length <= 16
# 	words[i] only consists of lowercase English letters.
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
# - String Sorts (array, string, recursion)
#   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
#   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
#   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
#   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
#   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
# - D´Esopo-Pape algorithm (array, deque, bellman-ford)
#   • When to use: Use this algorithm for finding single-source shortest paths in graphs with non-negative or negative edge weights, but without negative cycles. It is often faster than Bellman-Ford in practice for many graph types.
#   • Idea: The D'Esopo-Pape algorithm finds single-source shortest paths in graphs with negative edge weights (no negative cycles) by using a deque to manage vertex relaxation across three distinct sets. It offers an average time complexity often better than O(VE), though worst-case remains O(VE).
#   • Invariants: For any vertex v, d[v] is always an upper bound on the true shortest path distance from the source.; All vertices currently in M1 are present in the deque.
#   • Tips: Utilize a deque to efficiently manage vertices in the M1 set.; Prioritize re-inserting M0 vertices to the front of the deque for faster re-evaluation.
#   • Pitfalls: The algorithm does not correctly handle graphs containing negative cycles.; Can be slower than Dijkstra's algorithm for graphs with only non-negative edge weights.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def longestStrChain(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        words.sort(key=len)
        dp = {}
        max_chain_length = 1

        for word in words:
            dp[word] = 1  # Each word is at least a chain of length 1
            for i in range(len(word)):
                predecessor = word[:i] + word[i+1:]  # Remove one character
                if predecessor in dp:
                    dp[word] = max(dp[word], dp[predecessor] + 1)
            max_chain_length = max(max_chain_length, dp[word])

        return max_chain_length