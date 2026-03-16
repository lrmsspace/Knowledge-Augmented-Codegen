# Source: https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a binary string s and an integer k.
#
# You are also given a 2D integer array queries, where queries[i] = [li, ri].
#
# A binary string satisfies the k-constraint if either of the following conditions holds:
#
#
# 	The number of 0's in the string is at most k.
# 	The number of 1's in the string is at most k.
#
#
# Return an integer array answer, where answer[i] is the number of substrings of s[li..ri] that satisfy the k-constraint.
#
# Example:
# Input: s = "0001111", k = 2, queries = [[0,6]]
#
# Output: [26]
#
# Explanation:
#
# For the query [0, 6], all substrings of s[0..6] = "0001111" satisfy the k-constraint except for the substrings s[0..5] = "000111" and s[0..6] = "0001111".
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either '0' or '1'.
# 	1 <= k <= s.length
# 	1 <= queries.length <= 105
# 	queries[i] == [li, ri]
# 	0 <= li <= ri < s.length
# 	All queries are distinct.
#
# Helpful references (internal KB):
# - Fenwick Tree (array, bit-fenwick, difference-array)
#   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
#   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
#   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
#   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
#   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
# - Sqrt Tree (array, number, bitmask-dp, enumeration)
#   • When to use: Used for answering range queries on a static array by recursively decomposing it into square root sized blocks, achieving O(log log N) query time.
#   • Idea: A Sqrt Tree is a recursive data structure that decomposes an array into blocks of square root size, building a similar structure on each block. It allows for efficient range queries, typically achieving O(log log N) query time after an O(N log log N) precomputation.
#   • Invariants: Each node in the Sqrt Tree represents a contiguous segment of the original array.; A node representing a segment of length k has sqrt(k) children, each covering a block of sqrt(k) elements.
#   • Tips: Precompute answers for all possible block combinations within a node.; Handle queries spanning multiple blocks by combining precomputed prefix, suffix, and full block results.
#   • Pitfalls: High constant factors due to complex precomputation per node.; Memory usage can be significant, O(N log log N), for large N.
# - Generating all K-combinations (bitset, enumeration)
#   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
#   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
#   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
#   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
#   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countKConstraintSubstrings(self, s, k, queries):
        """
        :type s: str
        :type k: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # Precompute prefix sums for '0's and '1's
        n = len(s)
        prefix_0 = [0] * (n + 1)
        prefix_1 = [0] * (n + 1)

        for i in range(n):
            prefix_0[i + 1] = prefix_0[i] + (s[i] == '0')
            prefix_1[i + 1] = prefix_1[i] + (s[i] == '1')

        def count_valid_substrings(l, r):
            total_substrings = (r - l + 1) * (r - l + 2) // 2
            count_0 = prefix_0[r + 1] - prefix_0[l]
            count_1 = prefix_1[r + 1] - prefix_1[l]

            if count_0 > k and count_1 > k:
                return total_substrings - ((count_0 - k) * (count_1 - k))
            return total_substrings

        results = []
        for li, ri in queries:
            results.append(count_valid_substrings(li, ri))

        return results