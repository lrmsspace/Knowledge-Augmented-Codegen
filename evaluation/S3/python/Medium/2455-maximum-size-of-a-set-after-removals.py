# Source: https://leetcode.com/problems/maximum-size-of-a-set-after-removals/   |   Difficulty: Medium
#
# Problem Description:
# You are given two 0-indexed integer arrays nums1 and nums2 of even length n.
#
# You must remove n / 2 elements from nums1 and n / 2 elements from nums2. After the removals, you insert the remaining elements of nums1 and nums2 into a set s.
#
# Return the maximum possible size of the set s.
#
# Example:
# Input: nums1 = [1,2,1,2], nums2 = [1,1,1,1]
# Output: 2
# Explanation: We remove two occurences of 1 from nums1 and nums2. After the removals, the arrays become equal to nums1 = [2,2] and nums2 = [1,1]. Therefore, s = {1,2}.
# It can be shown that 2 is the maximum possible size of the set s after the removals.
#
# Constraints:
# n == nums1.length == nums2.length
# 	1 <= n <= 2 * 104
# 	n is even.
# 	1 <= nums1[i], nums2[i] <= 109
#
# Helpful references (internal KB):
# - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
#   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
#   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
#   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
#   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
#   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
#   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
#   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
#   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
#   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
#   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumSetSize(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        from collections import Counter

        count1 = Counter(nums1)
        count2 = Counter(nums2)

        # Calculate the number of unique elements in nums1 and nums2
        unique_nums1 = len(count1)
        unique_nums2 = len(count2)

        # Calculate the number of common unique elements
        common_unique = len(set(count1.keys()) & set(count2.keys()))

        # The maximum size of the set after removals is the total unique elements minus the common ones
        max_set_size = (unique_nums1 + unique_nums2) - common_unique

        return max_set_size