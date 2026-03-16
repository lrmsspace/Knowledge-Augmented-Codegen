# Source: https://leetcode.com/problems/find-the-shortest-superstring/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of strings words, return the smallest string that contains each string in words as a substring. If there are multiple valid strings of the smallest length, return any of them.
#
# You may assume that no string in words is a substring of another string in words.
#
# Example:
# Input: words = ["alex","loves","leetcode"]
# Output: "alexlovesleetcode"
# Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
#
# Constraints:
# 1 <= words.length <= 12
# 	1 <= words[i].length <= 20
# 	words[i] consists of lowercase English letters.
# 	All the strings of words are unique.
#
# Helpful references (internal KB):
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
# - Lyndon factorization (string, greedy, two-pointers)
#   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
#   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
#   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
#   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
#   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shortestSuperstring(self, words):
        """
        :type words: List[str]
        :rtype: str
        """
        n = len(words)
        
        # Step 1: Compute overlap between words
        overlap = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if i != j:
                    max_ov = min(len(words[i]), len(words[j]))
                    for k in range(max_ov, 0, -1):
                        if words[i][-k:] == words[j][:k]:
                            overlap[i][j] = k
                            break
        
        # Step 2: DP to find the maximum overlap path
        dp = [[0] * n for _ in range(1 << n)]
        parent = [[-1] * n for _ in range(1 << n)]
        
        for mask in range(1 << n):
            for u in range(n):
                if not (mask & (1 << u)):
                    continue
                prev_mask = mask ^ (1 << u)
                if prev_mask == 0:
                    continue
                for v in range(n):
                    if not (prev_mask & (1 << v)):
                        continue
                    cost = dp[prev_mask][v] + overlap[v][u]
                    if cost > dp[mask][u]:
                        dp[mask][u] = cost
                        parent[mask][u] = v
        
        # Step 3: Reconstruct the path
        max_len = -1
        last = -1
        final_mask = (1 << n) - 1
        for i in range(n):
            if dp[final_mask][i] > max_len:
                max_len = dp[final_mask][i]
                last = i
        
        path = []
        mask = final_mask
        while last != -1:
            path.append(last)
            temp = parent[mask][last]
            mask ^= (1 << last)
            last = temp
        path.reverse()
        
        # Step 4: Build the superstring
        superstring = words[path[0]]
        for i in range(1, len(path)):
            ov = overlap[path[i - 1]][path[i]]
            superstring += words[path[i]][ov:]
        
        return superstring