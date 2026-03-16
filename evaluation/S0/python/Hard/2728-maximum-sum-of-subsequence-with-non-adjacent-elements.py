# Source: https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums consisting of integers. You are also given a 2D array queries, where queries[i] = [posi, xi].
#
# For query i, we first set nums[posi] equal to xi, then we calculate the answer to query i which is the maximum sum of a subsequence of nums where no two adjacent elements are selected.
#
# Return the sum of the answers to all queries.
#
# Since the final answer may be very large, return it modulo 109 + 7.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: nums = [3,5,9], queries = [[1,-2],[0,-3]]
#
# Output: 21
#
# Explanation:
# After the 1st query, nums = [3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 3 + 9 = 12.
# After the 2nd query, nums = [-3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 9.
#
# Constraints:
# 1 <= nums.length <= 5 * 104
# 	-105 <= nums[i] <= 105
# 	1 <= queries.length <= 5 * 104
# 	queries[i] == [posi, xi]
# 	0 <= posi <= nums.length - 1
# 	-105 <= xi <= 105
#

class Solution(object):
    def maximumSumSubsequence(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        
        def max_sum_non_adjacent(arr):
            incl = 0
            excl = 0
            
            for num in arr:
                new_excl = max(incl, excl)
                incl = excl + max(0, num)
                excl = new_excl
            
            return max(incl, excl)
        
        total_sum = 0
        
        for pos, x in queries:
            nums[pos] = x
            total_sum = (total_sum + max_sum_non_adjacent(nums)) % MOD
        
        return total_sum