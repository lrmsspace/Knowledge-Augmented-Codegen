# Source: https://leetcode.com/problems/shifting-letters-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s of lowercase English letters and a 2D integer array shifts where shifts[i] = [starti, endi, directioni]. For every i, shift the characters in s from the index starti to the index endi (inclusive) forward if directioni = 1, or shift the characters backward if directioni = 0.
#
# Shifting a character forward means replacing it with the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Similarly, shifting a character backward means replacing it with the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').
#
# Return the final string after all such shifts to s are applied.
#
# Example:
# Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
# Output: "ace"
# Explanation: Firstly, shift the characters from index 0 to index 1 backward. Now s = "zac".
# Secondly, shift the characters from index 1 to index 2 forward. Now s = "zbd".
# Finally, shift the characters from index 0 to index 2 forward. Now s = "ace".
#
# Constraints:
# 1 <= s.length, shifts.length <= 5 * 104
# 	shifts[i].length == 3
# 	0 <= starti <= endi < s.length
# 	0 <= directioni <= 1
# 	s consists of lowercase English letters.
#
# Helpful references (internal KB):
# - Range Minimum Query (array, ds, union-find)
#   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
#   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
#   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
#   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
#   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
# - Suffix Automaton (graph, string, simulation)
#   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
#   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
#   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
#   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
#   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shiftingLetters(self, s, shifts):
        """
        :type s: str
        :type shifts: List[List[int]]
        :rtype: str
        """
        n = len(s)
        diff = [0] * (n + 1)

        for start, end, direction in shifts:
            if direction == 1:
                diff[start] += 1
                diff[end + 1] -= 1
            else:
                diff[start] -= 1
                diff[end + 1] += 1

        for i in range(1, n):
            diff[i] += diff[i - 1]

        result = []
        for i in range(n):
            shift = diff[i] % 26
            new_char = chr((ord(s[i]) - ord('a') + shift) % 26 + ord('a'))
            result.append(new_char)

        return ''.join(result)