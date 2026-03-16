# Source: https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array target. You have an integer array initial of the same size as target with all elements initially zeros.
#
# In one operation you can choose any subarray from initial and increment each value by one.
#
# Return the minimum number of operations to form a target array from initial.
#
# The test cases are generated so that the answer fits in a 32-bit integer.
#
# Example:
# Input: target = [1,2,3,2,1]
# Output: 3
# Explanation: We need at least 3 operations to form the target array from the initial array.
# [0,0,0,0,0] increment 1 from index 0 to 4 (inclusive).
# [1,1,1,1,1] increment 1 from index 1 to 3 (inclusive).
# [1,2,2,2,1] increment 1 at index 2.
# [1,2,3,2,1] target array is formed.
#
# Constraints:
# 1 <= target.length <= 105
# 	1 <= target[i] <= 105
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Minimum stack / Minimum queue (queue, deque, monotonic-queue)
#   • When to use: Use this technique when you need to perform standard queue or stack operations while also querying the minimum (or maximum) element in O(1) time. It is ideal for problems involving sliding windows or dynamic collections where min/max queries are frequent.
#   • Idea: This technique augments a queue or stack with an auxiliary data structure, typically a deque, to maintain elements in monotonic order. This allows for O(1) retrieval of the minimum (or maximum) element, with standard operations achieving amortized O(1) time complexity.
#   • Invariants: The auxiliary deque stores elements in non-decreasing order from front to back.; The element at the front of the auxiliary deque is the minimum of all elements currently in the main queue/stack.
#   • Tips: Utilize a deque for the auxiliary structure to efficiently add and remove from both ends.; For a minimum queue, maintain the auxiliary deque in non-decreasing order from front to back.
#   • Pitfalls: Incorrectly handling removals when the element to be removed from the main structure is not the current minimum.; Forgetting to remove elements from the auxiliary deque when they are no longer relevant (e.g., out of window bounds).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minNumberOperations(self, target):
        """
        :type target: List[int]
        :rtype: int
        """
        # The minimum number of operations needed to form the target array is equal to the sum of the positive differences between consecutive elements in the target array, plus the value of the first element (if it's greater than zero).
        # This is because each operation can increment a contiguous subarray, and we need to account for the increments needed to reach each element from the previous one.

        if not target:
            return 0

        operations = target[0]  # Start with the first element's value (if it's greater than zero)
        
        for i in range(1, len(target)):
            if target[i] > target[i - 1]:
                operations += target[i] - target[i - 1]

        return operations