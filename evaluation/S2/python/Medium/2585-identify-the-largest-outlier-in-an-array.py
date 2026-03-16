# Source: https://leetcode.com/problems/identify-the-largest-outlier-in-an-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums. This array contains n elements, where exactly n - 2 elements are special numbers. One of the remaining two elements is the sum of these special numbers, and the other is an outlier.
#
# An outlier is defined as a number that is neither one of the original special numbers nor the element representing the sum of those numbers.
#
# Note that special numbers, the sum element, and the outlier must have distinct indices, but may share the same value.
#
# Return the largest potential outlier in nums.
#
# Example:
# Input: nums = [2,3,5,10]
#
# Output: 10
#
# Explanation:
#
# The special numbers could be 2 and 3, thus making their sum 5 and the outlier 10.
#
# Constraints:
# 3 <= nums.length <= 105
# 	-1000 <= nums[i] <= 1000
# 	The input is generated such that at least one potential outlier exists in nums.
#
# Helpful references (internal KB):
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
# - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
#   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
#   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
#   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
#   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
#   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
# - kth-largest-element-in-an-array (array, merge-sort)
#   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
#   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
#   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
#   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
#   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getLargestOutlier(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        total_sum = sum(nums)
        max_outlier = float('-inf')
        
        for num in nums:
            potential_sum = total_sum - num
            if potential_sum in nums and potential_sum != num:
                max_outlier = max(max_outlier, num)
        
        return max_outlier