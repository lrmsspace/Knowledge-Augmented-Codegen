# Source: https://leetcode.com/problems/block-placement-queries/   |   Difficulty: Hard
#
# Problem Description:
# There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.
#
# You are given a 2D array queries, which contains two types of queries:
#
#
# 	For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
# 	For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
#
#
# Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.
#
# Example:
# Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]
#
# Output: [false,true,true]
#
# Explanation:
#
#
#
# For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.
#
# Constraints:
# 1 <= queries.length <= 15 * 104
# 	2 <= queries[i].length <= 3
# 	1 <= queries[i][0] <= 2
# 	1 <= x, sz <= min(5 * 104, 3 * queries.length)
# 	The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
# 	The input is generated such that there is at least one query of type 2.
#
# Helpful references (internal KB):
# - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
#   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
#   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
#   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
#   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
#   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
# - MEX (minimal excluded) of a sequence (ds, enumeration)
#   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
#   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
#   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
#   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
#   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
# - Point location in O(logn) (geometry, ds, simulation)
#   • When to use: Use when needing to efficiently determine which region (face or edge) of a planar subdivision a given query point lies within, especially for multiple online queries.
#   • Idea: This algorithm preprocesses a planar subdivision to answer point location queries in logarithmic time. It typically involves building a specialized data structure, possibly persistent, to quickly identify the containing face or edge for any given point.
#   • Invariants: The search process always maintains the invariant that the query point is within the current candidate region.; After each step, the search space for the point's location is reduced by a constant factor.
#   • Tips: Use a suitable geometric data structure like a trapezoidal map or persistent segment tree.; Carefully handle points lying exactly on edges or vertices.
#   • Pitfalls: Degenerate cases (vertical edges, collinear points) require careful handling.; Floating-point precision errors can lead to incorrect classifications.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getResults(self, queries):
        """
        :type queries: List[List[int]]
        :rtype: List[bool]
        """
        import bisect

        class SegmentTree:
            def __init__(self, size):
                self.size = size
                self.tree = [0] * (4 * size)

            def update(self, idx, value, node, node_left, node_right):
                if node_left == node_right:
                    self.tree[node] += value
                    return
                mid = (node_left + node_right) // 2
                if idx <= mid:
                    self.update(idx, value, 2 * node + 1, node_left, mid)
                else:
                    self.update(idx, value, 2 * node + 2, mid + 1, node_right)
                self.tree[node] = self.tree[2 * node + 1] + self.tree[2 * node + 2]

            def query(self, left, right, node, node_left, node_right):
                if right < node_left or left > node_right:
                    return 0
                if left <= node_left and node_right <= right:
                    return self.tree[node]
                mid = (node_left + node_right) // 2
                return (self.query(left, right, 2 * node + 1, node_left, mid) +
                        self.query(left, right, 2 * node + 2, mid + 1, node_right))

        max_x = 50000
        seg_tree = SegmentTree(max_x + 1)
        results = []

        for query in queries:
            if query[0] == 1:
                x = query[1]
                seg_tree.update(x, 1, 0, 0, max_x)
            else:
                x, sz = query[1], query[2]
                total_blocks = seg_tree.query(0, x, 0, 0, max_x)
                can_place = (x + 1 - total_blocks) >= sz
                results.append(can_place)

        return results