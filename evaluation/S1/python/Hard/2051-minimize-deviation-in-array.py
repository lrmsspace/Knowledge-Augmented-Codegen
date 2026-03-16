# Source: https://leetcode.com/problems/minimize-deviation-in-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums of n positive integers.
#
# You can perform two types of operations on any element of the array any number of times:
#
#
# 	If the element is even, divide it by 2.
#
# 	
# 		For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
# 	
# 	
# 	If the element is odd, multiply it by 2.
# 	
# 		For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
# 	
# 	
#
#
# The deviation of the array is the maximum difference between any two elements in the array.
#
# Return the minimum deviation the array can have after performing some number of operations.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: 1
# Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.
#
# Constraints:
# n == nums.length
# 	2 <= n <= 5 * 104
# 	1 <= nums[i] <= 109
#
# Helpful references (internal KB):
# - kth-largest-element-in-an-array (heap, array, heap-select)
#   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
#   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
#   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
#   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
#   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
# - Minimum stack / Minimum queue (queue, stack, simulation)
#   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
#   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
#   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
#   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
#   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumDeviation(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        import heapq

        # Step 1: Normalize the array by making all numbers even
        for i in range(len(nums)):
            if nums[i] % 2 == 1:  # If the number is odd
                nums[i] *= 2  # Make it even by multiplying by 2

        # Step 2: Create a max heap (using negative values for min-heap behavior)
        max_heap = [-num for num in nums]
        heapq.heapify(max_heap)

        # Step 3: Initialize the minimum deviation
        min_deviation = float('inf')

        while True:
            # Get the current maximum element (negate back to get original value)
            current_max = -max_heap[0]
            # Get the current minimum element (negate back to get original value)
            current_min = -max_heap[-1]

            # Update the minimum deviation
            min_deviation = min(min_deviation, current_max - current_min)

            # If the current maximum is even, we can reduce it
            if current_max % 2 == 0:
                # Pop the maximum element from the heap
                heapq.heappop(max_heap)
                # Push the reduced value back into the heap
                heapq.heappush(max_heap, -(current_max // 2))
            else:
                # If the maximum is odd, we cannot reduce it further, break out of the loop
                break

        return min_deviation