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
# - Fenwick Tree (array, bit-fenwick, difference-array)
#   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
#   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
#   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
#   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
#   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
#   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
#   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
#   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
#   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
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
        
        # Fenwick Tree (BIT) implementation
        bit = [0] * (n + 1)
        
        def update(i):
            while i <= n:
                bit[i] += 1
                i += i & -i
        
        def query(i):
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & -i
            return s
        
        operations = 0
        for num in sorted_nums:
            idx = index_map[num] + 1  # Convert to 1-based index
            operations += query(idx - 1)  # Count how many have been removed before this index
            update(idx)  # Mark this index as removed
        
        return operations