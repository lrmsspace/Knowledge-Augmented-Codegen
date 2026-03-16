# Source: https://leetcode.com/problems/make-array-empty/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums containing distinct numbers, and you can perform the following operations until the array is empty:
#
#
# 	If the first element has the smallest value, remove it
# 	Otherwise, put the first element at the end of the array.
#
#
# Return an integer denoting the number of operations it takes to make nums empty.
#
# Example:
# Input: nums = [3,4,-1]
# Output: 5
#
#
#
# 	
# 		
# 			Operation
# 			Array
# 		
# 	
# 	
# 		
# 			1
# 			[4, -1, 3]
# 		
# 		
# 			2
# 			[-1, 3, 4]
# 		
# 		
# 			3
# 			[3, 4]
# 		
# 		
# 			4
# 			[4]
# 		
# 		
# 			5
# 			[]
#
# Constraints:
# 1 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
# 	All values in nums are distinct.
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d, binary-search)
#   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
#   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
#   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
#   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
#   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
# - Minimum stack / Minimum queue (queue, stack, simulation)
#   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
#   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
#   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
#   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
#   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
# -  
# Kth order statistic in O(N) (array, enumeration)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
#   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
#   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
#   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countOperationsToEmptyArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        sorted_nums = sorted(nums)
        index_map = {num: i for i, num in enumerate(nums)}
        
        # Calculate the number of operations needed
        operations = 0
        for i in range(n):
            current_index = index_map[sorted_nums[i]]
            operations += current_index + 1  # +1 for the removal operation
            
            # Update the indices of the remaining elements
            for j in range(i + 1, n):
                if index_map[sorted_nums[j]] > current_index:
                    index_map[sorted_nums[j]] -= 1
        
        return operations