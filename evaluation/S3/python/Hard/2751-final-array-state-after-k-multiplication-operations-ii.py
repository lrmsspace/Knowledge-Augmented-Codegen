# Source: https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums, an integer k, and an integer multiplier.
#
# You need to perform k operations on nums. In each operation:
#
#
# 	Find the minimum value x in nums. If there are multiple occurrences of the minimum value, select the one that appears first.
# 	Replace the selected minimum value x with x * multiplier.
#
#
# After the k operations, apply modulo 109 + 7 to every value in nums.
#
# Return an integer array denoting the final state of nums after performing all k operations and then applying the modulo.
#
# Example:
# Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
#
# Output: [8,4,6,5,6]
#
# Explanation:
#
#
# 	
# 		
# 			Operation
# 			Result
# 		
# 		
# 			After operation 1
# 			[2, 2, 3, 5, 6]
# 		
# 		
# 			After operation 2
# 			[4, 2, 3, 5, 6]
# 		
# 		
# 			After operation 3
# 			[4, 4, 3, 5, 6]
# 		
# 		
# 			After operation 4
# 			[4, 4, 6, 5, 6]
# 		
# 		
# 			After operation 5
# 			[8, 4, 6, 5, 6]
# 		
# 		
# 			After applying modulo
# 			[8, 4, 6, 5, 6]
#
# Constraints:
# 1 <= nums.length <= 104
# 	1 <= nums[i] <= 109
# 	1 <= k <= 109
# 	1 <= multiplier <= 106
#
# Helpful references (internal KB):
# - kth-largest-element-in-an-array (heap, array, heap-select)
#   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
#   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
#   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
#   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
#   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
# - Minimum stack / Minimum queue (stack, simulation)
#   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
#   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
#   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
#   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
#   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
# - Priority Queues (array, heap, heap-select)
#   • When to use: Use when an in-place sorting algorithm with O(N log N) worst-case time complexity is required, especially when memory constraints are a concern. It's also applicable for efficiently finding the K largest/smallest elements.
#   • Idea: Heapsort is an in-place comparison-based sorting algorithm that uses a binary heap data structure. It first builds a max-heap from the input array, then repeatedly extracts the maximum element and places it at the end of the array, achieving O(N log N) time complexity.
#   • Invariants: During heap construction, the processed subarray forms a valid heap-ordered complete binary tree.; During sortdown, the elements in `arr[0...i]` form a valid heap, and `arr[i+1...N-1]` contains sorted elements.
#   • Tips: Heap construction can be done in linear time using a bottom-up sink-based approach.; Heapsort is an in-place sorting algorithm, requiring O(1) auxiliary space.
#   • Pitfalls: Heapsort is not a stable sorting algorithm; the relative order of equal elements is not preserved.; Cache performance can be poor due to non-sequential memory access patterns during heap operations.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getFinalState(self, nums, k, multiplier):
        """
        :type nums: List[int]
        :type k: int
        :type multiplier: int
        :rtype: List[int]
        """
        
        
        heap = [(num, i) for i, num in enumerate(nums)]
        heapq.heapify(heap)
        for _ in range(k):
            val, idx = heapq.heappop(heap)
            nums[idx] = val * multiplier
            heapq.heappush(heap, (nums[idx], idx))
        return nums