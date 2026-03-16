# Source: https://leetcode.com/problems/maximum-subarray-min-product/   |   Difficulty: Medium
#
# Problem Description:
# The min-product of an array is equal to the minimum value in the array multiplied by the array's sum.
#
#
# 	For example, the array [3,2,5] (minimum value is 2) has a min-product of 2 * (3+2+5) = 2 * 10 = 20.
#
#
# Given an array of integers nums, return the maximum min-product of any non-empty subarray of nums. Since the answer may be large, return it modulo 109 + 7.
#
# Note that the min-product should be maximized before performing the modulo operation. Testcases are generated such that the maximum min-product without modulo will fit in a 64-bit signed integer.
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [1,2,3,2]
# Output: 14
# Explanation: The maximum min-product is achieved with the subarray [2,3,2] (minimum value is 2).
# 2 * (2+3+2) = 2 * 7 = 14.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 107
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
# - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
#   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
#   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
#   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
#   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
#   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
# - Submask Enumeration
#  (number, bitset, enumeration)
#   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
#   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
#   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
#   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
#   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxSumMinProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        
        # Compute prefix sums
        prefix_sums = [0] * (n + 1)
        for i in range(n):
            prefix_sums[i + 1] = prefix_sums[i] + nums[i]
        
        # Initialize stacks and boundary arrays
        left_bound = [-1] * n
        right_bound = [n] * n
        stack = []
        
        # Find left boundaries
        for i in range(n):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            if stack:
                left_bound[i] = stack[-1]
            stack.append(i)
        
        # Clear stack for right boundary calculation
        stack.clear()
        
        # Find right boundaries
        for i in range(n - 1, -1, -1):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            if stack:
                right_bound[i] = stack[-1]
            stack.append(i)
        
        # Calculate maximum min-product
        max_min_product = 0
        for i in range(n):
            total_sum = prefix_sums[right_bound[i]] - prefix_sums[left_bound[i] + 1]
            min_product = nums[i] * total_sum
            max_min_product = max(max_min_product, min_product)
        
        return max_min_product % MOD