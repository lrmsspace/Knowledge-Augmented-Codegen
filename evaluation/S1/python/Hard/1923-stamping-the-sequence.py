# Source: https://leetcode.com/problems/stamping-the-sequence/   |   Difficulty: Hard
#
# Problem Description:
# You are given two strings stamp and target. Initially, there is a string s of length target.length with all s[i] == '?'.
#
# In one turn, you can place stamp over s and replace every letter in the s with the corresponding letter from stamp.
#
#
# 	For example, if stamp = "abc" and target = "abcba", then s is "?????" initially. In one turn you can:
#
# 	
# 		place stamp at index 0 of s to obtain "abc??",
# 		place stamp at index 1 of s to obtain "?abc?", or
# 		place stamp at index 2 of s to obtain "??abc".
# 	
# 	Note that stamp must be fully contained in the boundaries of s in order to stamp (i.e., you cannot place stamp at index 3 of s).
#
#
# We want to convert s to target using at most 10 * target.length turns.
#
# Return an array of the index of the left-most letter being stamped at each turn. If we cannot obtain target from s within 10 * target.length turns, return an empty array.
#
# Example:
# Input: stamp = "abc", target = "ababc"
# Output: [0,2]
# Explanation: Initially s = "?????".
# - Place stamp at index 0 to get "abc??".
# - Place stamp at index 2 to get "ababc".
# [1,0,2] would also be accepted as an answer, as well as some other answers.
#
# Constraints:
# 1 <= stamp.length <= target.length <= 1000
# 	stamp and target consist of lowercase English letters.
#
# Helpful references (internal KB):
# - Breadth-first search (graph, array, bfs, counting)
#   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
#   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
#   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
#   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
# - Suffix Automaton (graph, string, simulation)
#   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
#   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
#   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
#   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
#   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def movesToStamp(self, stamp, target):
        """
        :type stamp: str
        :type target: str
        :rtype: List[int]
        """
        m, n = len(stamp), len(target)
        target = list(target)
        res = []
        while True:
            made_change = False
            for i in range(n - m + 1):
                if all(target[i + j] == '?' or target[i + j] == stamp[j] for j in range(m)):
                    for j in range(m):
                        target[i + j] = '?'
                    res.append(i)
                    made_change = True
            if not made_change:
                break
        return res[::-1] if all(c == '?' for c in target) else []