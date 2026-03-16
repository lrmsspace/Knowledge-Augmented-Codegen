# Source: https://leetcode.com/problems/maximum-xor-score-subarray-queries/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums of n integers, and a 2D integer array queries of size q, where queries[i] = [li, ri].
#
# For each query, you must find the maximum XOR score of any subarray of nums[li..ri].
#
# The XOR score of an array a is found by repeatedly applying the following operations on a so that only one element remains, that is the score:
#
#
# 	Simultaneously replace a[i] with a[i] XOR a[i + 1] for all indices i except the last one.
# 	Remove the last element of a.
#
#
# Return an array answer of size q where answer[i] is the answer to query i.
#
# Example:
# Input: nums = [2,8,4,32,16,1], queries = [[0,2],[1,4],[0,5]]
#
# Output: [12,60,60]
#
# Explanation:
#
# In the first query, nums[0..2] has 6 subarrays [2], [8], [4], [2, 8], [8, 4], and [2, 8, 4] each with a respective XOR score of 2, 8, 4, 10, 12, and 6. The answer for the query is 12, the largest of all XOR scores.
#
# In the second query, the subarray of nums[1..4] with the largest XOR score is nums[1..4] with a score of 60.
#
# In the third query, the subarray of nums[0..5] with the largest XOR score is nums[1..4] with a score of 60.
#
# Constraints:
# 1 <= n == nums.length <= 2000
# 	0 <= nums[i] <= 231 - 1
# 	1 <= q == queries.length <= 105
# 	queries[i].length == 2 
# 	queries[i] = [li, ri]
# 	0 <= li <= ri <= n - 1
#
# Helpful references (internal KB):
# - Sqrt Tree (array, tree, recursion)
#   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
#   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
#   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
#   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
#   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
# - Fenwick Tree (array, bit-fenwick, difference-array)
#   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
#   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
#   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
#   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
#   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
# - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
#   • When to use: Use when you need to perform O(1) range queries on a static array for an associative operation, after an O(N log N) preprocessing step.
#   • Idea: A data structure that precomputes answers for all possible range queries using an associative operation on a static array. It achieves O(1) query time and O(N log N) build time by storing prefix-like sums within logarithmically sized blocks.
#   • Invariants: For each level k, the array is partitioned into 2^k segments.; Within each segment, table[k][j] stores the result of the associative operation from j to the segment's midpoint (or midpoint to j).
#   • Tips: Ensure the operation is associative (e.g., min, max, sum, gcd, bitwise operations).; Preprocessing takes O(N log N) time and space.
#   • Pitfalls: Not suitable for mutable arrays; updates require rebuilding the table.; Requires O(N log N) memory, which can be substantial for very large N.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumSubarrayXor(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # Step 1: Precompute prefix XORs
        n = len(nums)
        prefix_xor = [0] * (n + 1)
        for i in range(n):
            prefix_xor[i + 1] = prefix_xor[i] ^ nums[i]

        # Step 2: Build a Sqrt Tree for maximum XOR queries
        block_size = int(n**0.5) + 1
        max_layer = block_size.bit_length()  # Number of layers needed
        tree = [[0] * n for _ in range(max_layer)]

        # Precompute the Sqrt Tree layers
        for k in range(max_layer):
            step = 1 << k
            for i in range(n):
                if i + step < n:
                    tree[k][i] = max(tree[k][i], tree[k][i + step])
                tree[k][i] = max(tree[k][i], prefix_xor[i])

        # Step 3: Process each query using the Sqrt Tree
        def query(l, r):
            if l == r:
                return nums[l]
            highest_bit = (l ^ r).bit_length() - 1
            return max(tree[highest_bit][l], tree[highest_bit][r])

        results = []
        for l, r in queries:
            results.append(query(l, r))

        return results