# Source: https://leetcode.com/problems/count-almost-equal-pairs-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums consisting of positive integers.
#
# We call two integers x and y in this problem almost equal if both integers can become equal after performing the following operation at most once:
#
#
# 	Choose either x or y and swap any two digits within the chosen number.
#
#
# Return the number of indices i and j in nums where i < j such that nums[i] and nums[j] are almost equal.
#
# Note that it is allowed for an integer to have leading zeros after performing an operation.
#
# Example:
# Input: nums = [3,12,30,17,21]
#
# Output: 2
#
# Explanation:
#
# The almost equal pairs of elements are:
#
#
# 	3 and 30. By swapping 3 and 0 in 30, you get 3.
# 	12 and 21. By swapping 1 and 2 in 12, you get 21.
#
# Constraints:
# 2 <= nums.length <= 100
# 	1 <= nums[i] <= 106
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
# - Finding the nearest pair of points (geometry, array, divide-and-conquer)
#   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
#   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
#   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
#   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
#   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countPairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import defaultdict

        def get_signature(num):
            digits = list(str(num))
            if len(digits) < 2:
                return ''.join(sorted(digits))
            signatures = set()
            for i in range(len(digits)):
                for j in range(i + 1, len(digits)):
                    # Swap digits at positions i and j
                    digits[i], digits[j] = digits[j], digits[i]
                    signatures.add(''.join(sorted(digits)))
                    # Swap back
                    digits[i], digits[j] = digits[j], digits[i]
            return min(signatures)

        signature_count = defaultdict(int)
        for num in nums:
            sig = get_signature(num)
            signature_count[sig] += 1

        result = 0
        for count in signature_count.values():
            if count > 1:
                result += count * (count - 1) // 2

        return result