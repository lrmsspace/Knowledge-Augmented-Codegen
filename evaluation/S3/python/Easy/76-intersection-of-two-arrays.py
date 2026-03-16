# Source: https://leetcode.com/problems/intersection-of-two-arrays/   |   Difficulty: Easy
#
# Problem Description:
# Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.
#
# Example:
# Input: nums1 = [1,2,2,1], nums2 = [2,2]
# Output: [2]
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 1000
# 	0 <= nums1[i], nums2[i] <= 1000
#
# Helpful references (internal KB):
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - Ordered Set - Python (ds, hashing)
#   • When to use: When you need a collection of unique items where the order of insertion must be preserved, allowing for efficient membership testing and iteration in that specific order.
#   • Idea: An ordered set stores unique elements while maintaining their original insertion order. It provides O(1) average time complexity for additions, deletions, and membership checks, typically implemented using a hash table combined with a linked list.
#   • Invariants: Every element within the set is unique.; The sequence of elements during iteration strictly follows their initial insertion order.
#   • Tips: In Python 3.7+, standard `dict`s maintain insertion order, effectively serving as ordered sets.; Use `collections.OrderedDict` for older Python versions or explicit semantic clarity.
#   • Pitfalls: Order is based on insertion, not value-based sorting; do not confuse the two.; Modifying an element's hash value while it's in the set can lead to undefined behavior.
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
    def intersection(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        set1 = set(nums1)
        set2 = set(nums2)
        return list(set1.intersection(set2))