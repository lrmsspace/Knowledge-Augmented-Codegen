# Source: https://leetcode.com/problems/number-of-unique-xor-triplets-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
#
# Return the number of unique XOR triplet values from all possible triplets (i, j, k).
#
# Example:
# Input: nums = [1,3]
#
# Output: 2
#
# Explanation:
#
# The possible XOR triplet values are:
#
#
# 	(0, 0, 0) → 1 XOR 1 XOR 1 = 1
# 	(0, 0, 1) → 1 XOR 1 XOR 3 = 3
# 	(0, 1, 1) → 1 XOR 3 XOR 3 = 1
# 	(1, 1, 1) → 3 XOR 3 XOR 3 = 3
#
#
# The unique XOR values are {1, 3}. Thus, the output is 2.
#
# Constraints:
# 1 <= nums.length <= 1500
# 	1 <= nums[i] <= 1500
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Sqrt Tree (array, tree, recursion)
#   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
#   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
#   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
#   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
#   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
# - Length of the union of segments (array, interval, sweep-line, counting)
#   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
#   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
#   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
#   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
#   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def uniqueXorTriplets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # Step 1: Count the frequency of each number in nums
        freq = {}
        for num in nums:
            freq[num] = freq.get(num, 0) + 1

        # Step 2: Generate all unique XOR triplet values
        unique_xor_values = set()
        unique_nums = list(freq.keys())

        for i in range(len(unique_nums)):
            for j in range(i, len(unique_nums)):
                for k in range(j, len(unique_nums)):
                    a, b, c = unique_nums[i], unique_nums[j], unique_nums[k]
                    xor_value = a ^ b ^ c
                    unique_xor_values.add(xor_value)

        # Step 3: Return the count of unique XOR triplet values
        return len(unique_xor_values)