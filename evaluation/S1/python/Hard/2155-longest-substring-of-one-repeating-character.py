# Source: https://leetcode.com/problems/longest-substring-of-one-repeating-character/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed string s. You are also given a 0-indexed string queryCharacters of length k and a 0-indexed array of integer indices queryIndices of length k, both of which are used to describe k queries.
#
# The ith query updates the character in s at index queryIndices[i] to the character queryCharacters[i].
#
# Return an array lengths of length k where lengths[i] is the length of the longest substring of s consisting of only one repeating character after the ith query is performed.
#
# Example:
# Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
# Output: [3,3,4]
# Explanation: 
# - 1st query updates s = "bbbacc". The longest substring consisting of one repeating character is "bbb" with length 3.
# - 2nd query updates s = "bbbccc". 
#   The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
# - 3rd query updates s = "bbbbcc". The longest substring consisting of one repeating character is "bbbb" with length 4.
# Thus, we return [3,3,4].
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters.
# 	k == queryCharacters.length == queryIndices.length
# 	1 <= k <= 105
# 	queryCharacters consists of lowercase English letters.
# 	0 <= queryIndices[i] < s.length
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
#   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
#   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
#   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
#   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
#   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
# - Suffix Automaton (graph, string, simulation)
#   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
#   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
#   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
#   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
#   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
# - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
#   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
#   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
#   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
#   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
#   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def longestRepeating(self, s, queryCharacters, queryIndices):
        """
        :type s: str
        :type queryCharacters: str
        :type queryIndices: List[int]
        :rtype: List[int]
        """
        import bisect

        n = len(s)
        s = list(s)

        # Step 1: Initialize segments
        segments = []
        start = 0
        for i in range(1, n):
            if s[i] != s[i - 1]:
                segments.append([start, i - 1])
                start = i
        segments.append([start, n - 1])

        # Helper function to find the segment containing index idx
        def find_segment(idx):
            left, right = 0, len(segments) - 1
            while left <= right:
                mid = (left + right) // 2
                if segments[mid][0] <= idx <= segments[mid][1]:
                    return mid
                elif idx < segments[mid][0]:
                    right = mid - 1
                else:
                    left = mid + 1
            return -1

        # Helper function to get the maximum segment length
        def max_segment_length():
            return max(end - start + 1 for start, end in segments)

        result = []
        for char, idx in zip(queryCharacters, queryIndices):
            if s[idx] == char:
                result.append(max_segment_length())
                continue

            seg_idx = find_segment(idx)
            start, end = segments[seg_idx]
            s[idx] = char

            # Split the current segment if necessary
            new_segments = []
            if start < idx:
                new_segments.append([start, idx - 1])
            new_segments.append([idx, idx])
            if idx < end:
                new_segments.append([idx + 1, end])

            # Merge with previous segment if same character
            if seg_idx > 0 and s[segments[seg_idx - 1][0]] == char:
                prev_start, prev_end = new_segments[0]
                new_segments[0] = [segments[seg_idx - 1][0], prev_end]
                seg_idx -= 1

            # Merge with next segment if same character
            if seg_idx + len(new_segments) < len(segments) and s[segments[seg_idx + len(new_segments)][0]] == char:
                next_start, next_end = new_segments[-1]
                new_segments[-1] = [next_start, segments[seg_idx + len(new_segments)][1]]

            # Update segments
            segments = segments[:seg_idx] + new_segments + segments[seg_idx + 1 + (len(new_segments) - 1):]
            result.append(max_segment_length())
        return result   