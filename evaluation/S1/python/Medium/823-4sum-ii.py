# Source: https://leetcode.com/problems/4sum-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given four integer arrays nums1, nums2, nums3, and nums4 all of length n, return the number of tuples (i, j, k, l) such that:
#
#
# 	0 <= i, j, k, l < n
# 	nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
#
# Example:
# Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
# Output: 2
# Explanation:
# The two tuples are:
# 1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
# 2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0
#
# Constraints:
# n == nums1.length
# 	n == nums2.length
# 	n == nums3.length
# 	n == nums4.length
# 	1 <= n <= 200
# 	-228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Fenwick Tree (array, bit-fenwick, prefix-sum)
#   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
#   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
#   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
#   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
#   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def fourSumCount(self, nums1, nums2, nums3, nums4):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type nums3: List[int]
        :type nums4: List[int]
        :rtype: int
        """
        from collections import defaultdict

        sum_count = defaultdict(int)

        # Calculate all possible sums of pairs from nums1 and nums2
        for a in nums1:
            for b in nums2:
                sum_count[a + b] += 1

        total_tuples = 0

        # For each possible sum of pairs from nums3 and nums4,
        # check if the negated sum exists in sum_count
        for c in nums3:
            for d in nums4:
                target = -(c + d)
                if target in sum_count:
                    total_tuples += sum_count[target]

        return total_tuples