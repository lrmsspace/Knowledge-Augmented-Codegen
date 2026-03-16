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
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
# - Sparse Table (array, sparse-table, enumeration)
#   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
#   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
#   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
#   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
#   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
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
    def maximumSubarrayXor(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(nums)
        q = len(queries)

        # Step 1: Precompute XOR of all subarrays
        xor_subarrays = [[0] * n for _ in range(n)]
        for i in range(n):
            xor_subarrays[i][i] = nums[i]
            for j in range(i + 1, n):
                xor_subarrays[i][j] = xor_subarrays[i][j - 1] ^ nums[j]

        # Step 2: For each query, find the maximum XOR score
        results = []
        for li, ri in queries:
            max_xor = 0
            for i in range(li, ri + 1):
                for j in range(i, ri + 1):
                    max_xor = max(max_xor, xor_subarrays[i][j])
            results.append(max_xor)

        return results