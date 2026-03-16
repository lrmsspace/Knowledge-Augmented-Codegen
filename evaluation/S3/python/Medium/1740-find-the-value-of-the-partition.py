# Source: https://leetcode.com/problems/find-the-value-of-the-partition/   |   Difficulty: Medium
#
# Problem Description:
# You are given a positive integer array nums.
#
# Partition nums into two arrays, nums1 and nums2, such that:
#
#
# 	Each element of the array nums belongs to either the array nums1 or the array nums2.
# 	Both arrays are non-empty.
# 	The value of the partition is minimized.
#
#
# The value of the partition is |max(nums1) - min(nums2)|.
#
# Here, max(nums1) denotes the maximum element of the array nums1, and min(nums2) denotes the minimum element of the array nums2.
#
# Return the integer denoting the value of such partition.
#
# Example:
# Input: nums = [1,3,2,4]
# Output: 1
# Explanation: We can partition the array nums into nums1 = [1,2] and nums2 = [3,4].
# - The maximum element of the array nums1 is equal to 2.
# - The minimum element of the array nums2 is equal to 3.
# The value of the partition is |2 - 3| = 1. 
# It can be proven that 1 is the minimum value out of all partitions.
#
# Constraints:
# 2 <= nums.length <= 105
# 	1 <= nums[i] <= 109
#
# Helpful references (internal KB):
# - kth-largest-element-in-an-array (array, merge-sort)
#   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
#   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
#   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
#   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
#   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
# - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
#   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
#   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
#   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
#   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
#   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
# - bucket-sort (array, bucket-sort)
#   • When to use: When the input elements are uniformly distributed across a specific range, allowing for efficient partitioning and sorting.
#   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket, then concatenates them. It achieves O(N+K) average time complexity, where N is elements and K is buckets, assuming uniform distribution.
#   • Invariants: All elements from the input are initially present in the unsorted collection.; After distribution, each element resides in exactly one bucket, corresponding to its value range.
#   • Tips: Choose the number of buckets carefully based on data range and distribution.; Use an efficient sorting algorithm for individual buckets (e.g., insertion sort for small buckets).
#   • Pitfalls: Poor performance with non-uniform data distribution, leading to elements clustering in few buckets.; Requires knowing the range of input values beforehand to define bucket boundaries.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findValueOfPartition(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        min_diff = float('inf')
        
        for i in range(1, len(nums)):
            diff = nums[i] - nums[i - 1]
            min_diff = min(min_diff, diff)
        
        return min_diff