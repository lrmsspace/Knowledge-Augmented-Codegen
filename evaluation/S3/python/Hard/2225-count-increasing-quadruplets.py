# Source: https://leetcode.com/problems/count-increasing-quadruplets/   |   Difficulty: Hard
#
# Problem Description:
# Given a 0-indexed integer array nums of size n containing all numbers from 1 to n, return the number of increasing quadruplets.
#
# A quadruplet (i, j, k, l) is increasing if:
#
#
# 	0 <= i < j < k < l < n, and
# 	nums[i] < nums[k] < nums[j] < nums[l].
#
# Example:
# Input: nums = [1,3,2,4,5]
# Output: 2
# Explanation: 
# - When i = 0, j = 1, k = 2, and l = 3, nums[i] < nums[k] < nums[j] < nums[l].
# - When i = 0, j = 1, k = 2, and l = 4, nums[i] < nums[k] < nums[j] < nums[l]. 
# There are no other quadruplets, so we return 2.
#
# Constraints:
# 4 <= nums.length <= 4000
# 	1 <= nums[i] <= nums.length
# 	All the integers of nums are unique. nums is a permutation.
#
# Helpful references (internal KB):
# - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
#   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
#   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
#   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
#   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
#   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
# - Sparse Table (array, sparse-table, enumeration)
#   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
#   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
#   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
#   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
#   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countQuadruplets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        count = 0

        # Precompute the count of elements greater than nums[j] to the right of j
        greater_count = [[0] * n for _ in range(n)]
        for j in range(n):
            for k in range(j + 1, n):
                if nums[k] > nums[j]:
                    greater_count[j][k] = greater_count[j][k - 1] + 1
                else:
                    greater_count[j][k] = greater_count[j][k - 1]

        # Count quadruplets
        for i in range(n):
            for j in range(i + 1, n):
                if nums[i] < nums[j]:
                    for k in range(j + 1, n):
                        if nums[k] > nums[i] and nums[k] < nums[j]:
                            count += greater_count[j][n - 1] - greater_count[j][k]

        return count