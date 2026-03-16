# Source: https://leetcode.com/problems/maximum-product-of-three-numbers/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums, find three numbers whose product is maximum and return the maximum product.
#
# Example:
# Input: nums = [1,2,3]
# Output: 6
#
# Constraints:
# 3 <= nums.length <= 104
# 	-1000 <= nums[i] <= 1000
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - kth-largest-element-in-an-array (heap, array, heap-select)
#   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
#   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
#   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
#   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
#   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
# - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
#   • When to use: Use this method to efficiently calculate the determinant of a square matrix, especially when an LU decomposition is also beneficial for other linear algebra tasks like solving systems of equations.
#   • Idea: The Kraut method, a specific form of LU decomposition, factorizes a square matrix A into a lower triangular matrix L (with ones on the diagonal) and an upper triangular matrix U. The determinant of A is then computed as the product of all diagonal elements of U, achieving an O(N^3) time complexity.
#   • Invariants: After processing column k-1, the k-1th column of L and k-1th row of U are correctly determined.; The submatrix A[0...k-1][0...k-1] is equivalent to L[0...k-1][0...k-1] * U[0...k-1][0...k-1].
#   • Tips: Ensure the matrix is invertible for a unique LU decomposition without pivoting.; The diagonal elements of the L matrix are typically set to 1 for uniqueness in Kraut's method.
#   • Pitfalls: Division by zero can occur if a pivot element is zero, indicating a singular matrix or requiring pivoting strategies.; Numerical instability may arise with ill-conditioned matrices when using floating-point arithmetic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        return max(nums[0] * nums[1] * nums[-1], nums[-1] * nums[-2] * nums[-3])