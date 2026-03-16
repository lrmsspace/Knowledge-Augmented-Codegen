# Source: https://leetcode.com/problems/k-th-smallest-prime-fraction/   |   Difficulty: Medium
#
# Problem Description:
# You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.
#
# For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].
#
# Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].
#
# Example:
# Input: arr = [1,2,3,5], k = 3
# Output: [2,5]
# Explanation: The fractions to be considered in sorted order are:
# 1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
# The third fraction is 2/5.
#
# Constraints:
# 2 <= arr.length <= 1000
# 	1 <= arr[i] <= 3 * 104
# 	arr[0] == 1
# 	arr[i] is a prime number for i > 0.
# 	All the numbers of arr are unique and sorted in strictly increasing order.
# 	1 <= k <= arr.length * (arr.length - 1) / 2
#
#
#  
# Follow up: Can you solve the problem with better than O(n2) complexity?
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - kth-largest-element-in-an-array (heap, array, heap-select)
#   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
#   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
#   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
#   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
#   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
# - Continued fractions (tree, number, binary-search, enumeration)
#   • When to use: Use when seeking the best rational approximations for real numbers or when analyzing properties of numbers related to their fractional parts. It is also applicable for solving certain linear Diophantine equations.
#   • Idea: Continued fractions represent a real number as a sequence of integers, providing a series of increasingly accurate rational approximations called convergents. The process is analogous to the Euclidean algorithm, typically having logarithmic complexity relative to the magnitude of the number's denominator.
#   • Invariants: The current remainder in the iterative process is always positive and less than 1.; Each successive convergent p_k/q_k has a denominator q_k that is strictly increasing.
#   • Tips: Understand the connection between continued fractions and the Euclidean algorithm for rational numbers.; Convergents provide the 'best' rational approximations for a given denominator size.
#   • Pitfalls: Numerical precision issues can arise when computing continued fractions for floating-point numbers.; Misinterpreting the 'best approximation' property; it's specific to denominator size.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def kthSmallestPrimeFraction(self, arr, k):
        """
        :type arr: List[int]
        :type k: int
        :rtype: List[int]
        """
        from fractions import Fraction
        import heapq

        n = len(arr)
        min_heap = []

        # Initialize the heap with the smallest fractions for each numerator
        for i in range(n - 1):
            frac = Fraction(arr[i], arr[n - 1])
            heapq.heappush(min_heap, (frac, i, n - 1))

        # Extract the smallest fraction k-1 times
        for _ in range(k - 1):
            frac, i, j = heapq.heappop(min_heap)
            if j - 1 > i:
                new_frac = Fraction(arr[i], arr[j - 1])
                heapq.heappush(min_heap, (new_frac, i, j - 1))

        # The k-th smallest fraction is now at the top of the heap
        kth_frac, i, j = heapq.heappop(min_heap)
        return [arr[i], arr[j]]