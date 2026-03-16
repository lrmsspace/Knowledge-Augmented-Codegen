# Source: https://leetcode.com/problems/decompress-run-length-encoded-list/   |   Difficulty: Easy
#
# Problem Description:
# We are given a list nums of integers representing a list compressed with run-length encoding.
#
# Consider each adjacent pair of elements [freq, val] = [nums[2*i], nums[2*i+1]] (with i >= 0).  For each such pair, there are freq elements with value val concatenated in a sublist. Concatenate all the sublists from left to right to generate the decompressed list.
#
# Return the decompressed list.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: [2,4,4,4]
# Explanation: The first pair [1,2] means we have freq = 1 and val = 2 so we generate the array [2].
# The second pair [3,4] means we have freq = 3 and val = 4 so we generate [4,4,4].
# At the end the concatenation [2] + [4,4,4] is [2,4,4,4].
#
# Constraints:
# 2 <= nums.length <= 100
# 	nums.length % 2 == 0
# 	1 <= nums[i] <= 100
#
# Helpful references (internal KB):
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
#   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
#   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
#   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
#   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
# - Sparse Table (array, sparse-table, enumeration)
#   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
#   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
#   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
#   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
#   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def decompressRLElist(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        decompressed = []
        for i in range(0, len(nums), 2):
            freq = nums[i]
            val = nums[i + 1]
            decompressed.extend([val] * freq)
        return decompressed