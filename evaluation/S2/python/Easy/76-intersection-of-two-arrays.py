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
# - The Inclusion-Exclusion Principle (array, number, counting, sieve)
#   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
#   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
#   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
#   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
#   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
# - Ordered Set - Python (ds, hashing)
#   • When to use: Use when you need a collection of unique items that also preserves the order in which items were first added. It's ideal for scenarios requiring both set-like behavior and predictable iteration order.
#   • Idea: An ordered set is a data structure that stores unique elements while maintaining their insertion order. It combines the O(1) average-case time complexity for additions, deletions, and lookups of a hash set with the ordered iteration of a list.
#   • Invariants: All elements within the ordered set are unique.; The iteration order of elements matches their original insertion order.
#   • Tips: Install via `pip install ordered_set` for Python environments.; Leverage for scenarios requiring both uniqueness and order preservation.
#   • Pitfalls: Not a built-in Python type; requires external module installation.; Performance might be marginally slower than a standard `set` due to order maintenance overhead.
# - Check if two segments intersect (geometry, number, simulation)
#   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
#   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
#   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
#   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
#   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
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
        # Convert nums1 to a set for O(1) lookups
        set_nums1 = set(nums1)
        
        # Use a set to store the intersection to ensure uniqueness
        intersection_set = set()
        
        # Iterate through nums2 and check for intersection
        for num in nums2:
            if num in set_nums1:
                intersection_set.add(num)
        
        # Convert the set back to a list before returning
        return list(intersection_set)