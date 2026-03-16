# Source: https://leetcode.com/problems/sort-array-by-parity/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.
#
# Return any array that satisfies this condition.
#
# Example:
# Input: nums = [3,1,2,4]
# Output: [2,4,3,1]
# Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
#
# Constraints:
# 1 <= nums.length <= 5000
# 	0 <= nums[i] <= 5000
#
# Helpful references (internal KB):
# - Quicksort (array, two-pointers, randomized)
#   • When to use: Use Quicksort for efficient in-place sorting of arrays, especially when average-case performance and cache efficiency are prioritized. It is suitable for large datasets where memory usage is a concern.
#   • Idea: Quicksort is a divide-and-conquer sorting algorithm that partitions an array around a pivot element, then recursively sorts the two resulting subarrays. Its average time complexity is O(N log N), but can degrade to O(N^2) in the worst case.
#   • Invariants: All elements to the left of the `lt` pointer are less than the pivot value.; All elements to the right of the `gt` pointer are greater than the pivot value.
#   • Tips: Randomly shuffle the input or choose a random pivot to ensure average-case performance.; Employ 3-way partitioning to efficiently handle duplicate keys and avoid quadratic worst-case scenarios.
#   • Pitfalls: Failing to handle duplicate keys can lead to quadratic time complexity.; Incorrect pointer crossing logic can cause infinite loops or array out-of-bounds errors.
# - Minkowski sum of convex polygons (geometry, array, two-pointers, sweep-line)
#   • When to use: Use this algorithm to compute the Minkowski sum of two convex polygons efficiently. It is ideal for applications requiring the union of shapes or collision detection between convex objects.
#   • Idea: This algorithm computes the Minkowski sum of two convex polygons by merging their edge vectors, sorted by polar angle, into a new sequence of edges. The resulting sum polygon is also convex and can be constructed in O(|P| + |Q|) time.
#   • Invariants: The current vertex of the resulting sum polygon is the sum of the current vertices from P and Q.; All edges processed so far from both input polygons have been added to the output in polar angle order.
#   • Tips: Pre-sort polygon vertices to start from the lowest Y-coordinate to ensure consistent orientation.; Orient both input polygons counter-clockwise for correct edge vector generation.
#   • Pitfalls: Incorrectly handling polygon orientation (e.g., mixing clockwise and counter-clockwise).; Precision issues when using floating-point numbers for angle comparisons or vector additions.
# - bucket-sort (array, bucket-sort)
#   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
#   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
#   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
#   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
#   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def sortArrayByParity(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        even = []
        odd = []
        for num in nums:
            if num % 2 == 0:
                even.append(num)
            else:
                odd.append(num)
        return even + odd