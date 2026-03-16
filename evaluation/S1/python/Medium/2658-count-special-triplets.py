# Source: https://leetcode.com/problems/count-special-triplets/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# A special triplet is defined as a triplet of indices (i, j, k) such that:
#
#
# 	0 <= i < j < k < n, where n = nums.length
# 	nums[i] == nums[j] * 2
# 	nums[k] == nums[j] * 2
#
#
# Return the total number of special triplets in the array.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [6,3,6]
#
# Output: 1
#
# Explanation:
#
# The only special triplet is (i, j, k) = (0, 1, 2), where:
#
#
# 	nums[0] = 6, nums[1] = 3, nums[2] = 6
# 	nums[0] = nums[1] * 2 = 3 * 2 = 6
# 	nums[2] = nums[1] * 2 = 3 * 2 = 6
#
# Constraints:
# 3 <= n == nums.length <= 105
# 	0 <= nums[i] <= 105
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# -  
# Kth order statistic in O(N) (array, enumeration)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
#   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
#   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
#   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
# - Binomial Coefficients (array, enumeration)
#   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
#   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
#   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
#   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
#   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def specialTriplets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        count = 0
        n = len(nums)
        
        # Create a dictionary to store the frequency of each number
        freq = {}
        for num in nums:
            freq[num] = freq.get(num, 0) + 1
        
        # Iterate through each number as the middle element of the triplet
        for j in range(n):
            mid = nums[j]
            left = mid * 2
            right = mid * 2
            
            if left in freq and right in freq:
                count += freq[left] * freq[right]
                count %= MOD
        
        return count