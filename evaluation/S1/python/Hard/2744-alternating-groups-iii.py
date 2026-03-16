# Source: https://leetcode.com/problems/alternating-groups-iii/   |   Difficulty: Hard
#
# Problem Description:
# There are some red and blue tiles arranged circularly. You are given an array of integers colors and a 2D integers array queries.
#
# The color of tile i is represented by colors[i]:
#
#
#  colors[i] == 0 means that tile i is red.
#  colors[i] == 1 means that tile i is blue.
#
#
# An alternating group is a contiguous subset of tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its adjacent tiles in the group).
#
# You have to process queries of two types:
#
#
#  queries[i] = [1, sizei], determine the count of alternating groups with size sizei.
#  queries[i] = [2, indexi, colori], change colors[indexi] to colori.
#
#
# Return an array answer containing the results of the queries of the first type in order.
#
# Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.
#
# Example:
# Input: colors = [0,1,1,0,1], queries = [[2,1,0],[1,4]]
#
# Output: [2]
#
# Explanation:
#
#
#
# First query:
#
# Change colors[1] to 0.
#
#
#
# Second query:
#
# Count of the alternating groups with size 4:
#
# Constraints:
# 4 <= colors.length <= 5 * 104
#  0 <= colors[i] <= 1
#  1 <= queries.length <= 5 * 104
#  queries[i][0] == 1 or queries[i][0] == 2
#  For all i that:
#  
#   queries[i][0] == 1: queries[i].length == 2, 3 <= queries[i][1] <= colors.length - 1
#   queries[i][0] == 2: queries[i].length == 3, 0 <= queries[i][1] <= colors.length - 1, 0 <= queries[i][2] <= 1
#
# Helpful references (internal KB):
# - Sqrt Tree (array, tree, divide-and-conquer, recursion, prefix-sum)
#   • When to use: When performing associative range queries on an array, especially when O(1) query time is critical and O(N log log N) preprocessing is acceptable.
#   • Idea: The Sqrt Tree is a data structure that answers associative range queries on an array in O(1) time after O(N log log N) preprocessing. It achieves this by recursively applying sqrt decomposition, precomputing block-wise prefix/suffix operations and inter-block results.
#   • Invariants: The `prefixOp` array for any block `k` stores the associative sum from the block's start to each element within it.; The `suffixOp` array for any block `k` stores the associative sum from each element within it to the block's end.
#   • Tips: Ensure the operation is strictly associative for correctness.; Carefully handle block boundaries and partial blocks during query processing.
#   • Pitfalls: Using non-associative operations will yield incorrect results.; High memory usage for the 'between' array if not optimized or if N is very large.
# - Fenwick Tree (array, bit-fenwick, difference-array)
#   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
#   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
#   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
#   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
#   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
# - Treap (Cartesian tree) (tree, array, divide-and-conquer, recursion)
#   • When to use: Use when a dynamic data structure is needed to support efficient array-like operations (insert, delete, range queries/updates) on an ordered sequence, especially with frequent modifications at arbitrary positions.
#   • Idea: A Treap is a randomized binary search tree that maintains both BST properties on keys and heap properties on randomly assigned priorities. It supports various dynamic array operations and range queries/updates in expected O(log N) time.
#   • Invariants: For any node, its key is greater than all keys in its left subtree and less than all keys in its right subtree.; For any node, its priority is greater than or equal to the priorities of its children.
#   • Tips: Use random priorities to ensure probabilistic balance, avoiding worst-case O(N) operations.; Implement `split` and `merge` as fundamental building blocks for all other operations.
#   • Pitfalls: Forgetting to push lazy tags before accessing children or performing splits/merges.; Incorrectly updating `cnt` or aggregate fields after tree modifications.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfAlternatingGroups(self, colors, queries):
        """
        :type colors: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(colors)

        # Helper function to get the segments of alternating colors
        def get_segments():
            segments = []
            start = 0
            for i in range(1, n):
                if colors[i] == colors[i - 1]:
                    segments.append([start, i - 1])
                    start = i
            segments.append([start, n - 1])
            # Handle circular case
            if len(segments) > 1 and colors[0] == colors[-1]:
                first_segment = segments.pop(0)
                last_segment = segments.pop()
                merged_segment = [last_segment[0], first_segment[1] + n]
                segments.insert(0, merged_segment)
            return segments

        segments = get_segments()

        # Helper function to count segments of a given size
        def count_segments_of_size(size):
            count = 0
            for seg in segments:
                seg_size = seg[1] - seg[0] + 1
                if seg_size == size:
                    count += 1
            return count

        result = []
        for query in queries:
            if query[0] == 1:
                size = query[1]
                result.append(count_segments_of_size(size))
            else:
                index, new_color = query[1], query[2]
                if colors[index] == new_color:
                    continue  # No change needed
                colors[index] = new_color

                # Recompute segments after color change
                segments = get_segments()

        return result

            