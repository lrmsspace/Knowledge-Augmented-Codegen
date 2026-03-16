# Source: https://leetcode.com/problems/closest-equal-element-queries/   |   Difficulty: Medium
#
# Problem Description:
# You are given a circular array nums and an array queries.
#
# For each query i, you have to find the following:
#
#
# 	The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
#
#
# Return an array answer of the same size as queries, where answer[i] represents the result for query i.
#
# Example:
# Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
#
# Output: [2,-1,3]
#
# Explanation:
#
#
# 	Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
# 	Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
# 	Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
#
# Constraints:
# 1 <= queries.length <= nums.length <= 105
# 	1 <= nums[i] <= 106
# 	0 <= queries[i] < nums.length
#
# Helpful references (internal KB):
# - Sparse Table (array, sparse-table, enumeration)
#   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
#   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
#   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
#   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
#   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
# - String Hashing (string, number, hashing)
#   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
#   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
#   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
#   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
#   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
# - Minimum Enclosing Circle (array, geometry, randomized, recursion)
#   • When to use: Use when finding the smallest circle that contains a given set of 2D points. It provides an expected linear time solution for this fundamental geometric problem.
#   • Idea: Welzl's algorithm finds the unique minimum enclosing circle for a set of points using a randomized incremental approach. It achieves an expected time complexity of O(N).
#   • Invariants: The current candidate circle `C` encloses all points `p_1, ..., p_i` processed so far.; If `p_i` is not contained in `C_{i-1}`, then `p_i` must lie on the boundary of `C_i`.
#   • Tips: Randomly permute input points to ensure expected O(N) performance.; The MEC is uniquely determined by either two points forming a diameter or three points on its boundary.
#   • Pitfalls: Not randomizing the input can lead to a worst-case O(N^3) performance.; Floating-point precision issues can cause incorrect boundary checks or point containment tests.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def solveQueries(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[int]
        :rtype: List[int]
        """
        n = len(nums)
        index_map = {}
        result = []

        for i, num in enumerate(nums):
            if num not in index_map:
                index_map[num] = []
            index_map[num].append(i)

        for q in queries:
            target = nums[q]
            indices = index_map[target]

            if len(indices) == 1:
                result.append(-1)
                continue

            pos = self.binary_search(indices, q)
            left_index = indices[pos - 1] if pos > 0 else indices[-1] - n
            right_index = indices[pos] if pos < len(indices) else indices[0] + n

            dist_left = q - left_index
            dist_right = right_index - q

            result.append(min(dist_left, dist_right))

        return result